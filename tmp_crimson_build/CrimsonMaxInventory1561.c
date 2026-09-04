#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HMODULE g_self;
static HANDLE g_mutex;

#define GAME_TIMESTAMP 0x6A998DC4u
#define GAME_SIZE_IMAGE 0x16F1F000u
#define RADIUS 0x20000u
#define CHUNK_SIZE (256u*1024u)
#define MAX_A 64
#define MAX_B 128
#define MAX_C 128
#define MAX_D 256

static const unsigned char PAT_A[4]={0x32,0x00,0xF0,0x00};
static const unsigned char PAT_B[4]={0xF0,0x00,0xF0,0x00};
static const unsigned char PAT_C[4]={0xF0,0x00,0xE8,0x03};
static const unsigned char PAT_D[4]={0x0A,0x00,0xE8,0x03};
static const unsigned char NEW_732[4]={0xDC,0x02,0xDC,0x02};
static const unsigned char NEW_1440[4]={0xA0,0x05,0xA0,0x05};

static void zero_local(void*d,SIZE_T n){unsigned char*p=(unsigned char*)d;for(SIZE_T i=0;i<n;i++)p[i]=0;}
static int eq4(const unsigned char*a,const unsigned char*b){return a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3];}
static DWORD slen(const char*s){DWORD n=0;while(s&&s[n])n++;return n;}
static WCHAR lower_w(WCHAR c){if(c>=L'A'&&c<=L'Z')return c+(L'a'-L'A');return c;}
static int weq_ci(const WCHAR*a,const WCHAR*b){DWORD i=0;for(;;i++){WCHAR x=lower_w(a[i]),y=lower_w(b[i]);if(x!=y)return 0;if(!x)return 1;}}

static int current_process_is_game(void){
    WCHAR path[MAX_PATH*2];DWORD n=GetModuleFileNameW(NULL,path,MAX_PATH*2);if(!n||n>=MAX_PATH*2)return 0;
    WCHAR*base=path;for(DWORD i=0;i<n;i++)if(path[i]==L'\\'||path[i]==L'/')base=&path[i+1];
    return weq_ci(base,L"CrimsonDesert.exe");
}

static void make_log_path(WCHAR*out,DWORD cap){
    DWORD n=GetModuleFileNameW(g_self,out,cap);if(!n||n>=cap){if(cap)out[0]=0;return;}DWORD dot=n;
    for(DWORD i=0;i<n;i++){if(out[i]==L'\\'||out[i]==L'/')dot=n;else if(out[i]==L'.')dot=i;}
    if(dot==n){if(n+4>=cap){out[0]=0;return;}dot=n;}out[dot]=L'.';out[dot+1]=L'l';out[dot+2]=L'o';out[dot+3]=L'g';out[dot+4]=0;
}
static void log_line(const char*s){
    WCHAR p[MAX_PATH*2];zero_local(p,sizeof(p));make_log_path(p,MAX_PATH*2);if(!p[0])return;
    HANDLE h=CreateFileW(p,FILE_APPEND_DATA,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);if(h==INVALID_HANDLE_VALUE)return;
    DWORD w=0,n=slen(s);WriteFile(h,s,n,&w,NULL);static const char e[2]={'\r','\n'};WriteFile(h,e,2,&w,NULL);CloseHandle(h);
}

static int verify_game(void){
    HMODULE game=GetModuleHandleW(NULL);if(!game)return 0;unsigned char*b=(unsigned char*)game;IMAGE_DOS_HEADER*d=(IMAGE_DOS_HEADER*)b;if(d->e_magic!=IMAGE_DOS_SIGNATURE)return 0;
    IMAGE_NT_HEADERS64*n=(IMAGE_NT_HEADERS64*)(b+d->e_lfanew);if(n->Signature!=IMAGE_NT_SIGNATURE)return 0;
    return n->FileHeader.TimeDateStamp==GAME_TIMESTAMP&&n->OptionalHeader.SizeOfImage==GAME_SIZE_IMAGE;
}

#ifndef PROBE_ONLY

typedef ULONG_PTR uptr;
typedef struct{uptr a[MAX_A];int na,oa;uptr b[MAX_B];int nb,ob;uptr c[MAX_C];int nc,oc;uptr d[MAX_D];int nd,od;}AllMatches;
typedef struct{uptr a;uptr b;uptr c[MAX_C];int nc;uptr d[8];int nd;}Candidate;
typedef struct{unsigned char*addr;unsigned char oldv[4];const unsigned char*newv;int written;}Patch;

static AllMatches g_matches;
static unsigned char*g_buf;

static void add_unique(uptr*arr,int cap,int*n,int*overflow,uptr v){for(int i=0;i<*n;i++)if(arr[i]==v)return;if(*n<cap)arr[(*n)++]=v;else *overflow=1;}
static int prot_ok(DWORD p){if(p&PAGE_GUARD)return 0;p&=0xff;return p==PAGE_READWRITE||p==PAGE_WRITECOPY||p==PAGE_READONLY;}

static void scan_bytes(const unsigned char*buf,SIZE_T n,uptr va){
    if(n<4)return;for(SIZE_T i=0;i+4<=n;i++){
        const unsigned char*p=buf+i;uptr a=va+i;
        if(p[0]==0x32&&eq4(p,PAT_A))add_unique(g_matches.a,MAX_A,&g_matches.na,&g_matches.oa,a);
        else if(p[0]==0xF0){if(eq4(p,PAT_B))add_unique(g_matches.b,MAX_B,&g_matches.nb,&g_matches.ob,a);else if(eq4(p,PAT_C))add_unique(g_matches.c,MAX_C,&g_matches.nc,&g_matches.oc,a);}
        else if(p[0]==0x0A&&eq4(p,PAT_D))add_unique(g_matches.d,MAX_D,&g_matches.nd,&g_matches.od,a);
    }
}

static int collect_matches(void){
    zero_local(&g_matches,sizeof(g_matches));
    if(!g_buf){g_buf=(unsigned char*)VirtualAlloc(NULL,CHUNK_SIZE+4,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);if(!g_buf)return 0;}
    SYSTEM_INFO si;GetSystemInfo(&si);uptr addr=(uptr)si.lpMinimumApplicationAddress,maxa=(uptr)si.lpMaximumApplicationAddress;HANDLE proc=GetCurrentProcess();
    while(addr<maxa){MEMORY_BASIC_INFORMATION m;SIZE_T q=VirtualQuery((LPCVOID)addr,&m,sizeof(m));if(!q)break;uptr base=(uptr)m.BaseAddress,next=base+m.RegionSize;if(next<=addr)break;
        if(m.State==MEM_COMMIT&&(m.Type==MEM_PRIVATE||m.Type==MEM_MAPPED)&&prot_ok(m.Protect)){
            SIZE_T off=0;while(off<m.RegionSize){SIZE_T remain=m.RegionSize-off;SIZE_T want=remain>CHUNK_SIZE+3?CHUNK_SIZE+3:remain;SIZE_T got=0;
                if(ReadProcessMemory(proc,(LPCVOID)(base+off),g_buf,want,&got)&&got>=4){SIZE_T scan_n=got; if(remain>CHUNK_SIZE&&scan_n>CHUNK_SIZE+3)scan_n=CHUNK_SIZE+3;scan_bytes(g_buf,scan_n,base+off);}off+=CHUNK_SIZE;}
        }
        addr=next;
    }
    if(g_matches.oa||g_matches.ob||g_matches.oc||g_matches.od)return -1;return 1;
}

static int within(uptr x,uptr a){return x>=a-RADIUS&&x<=a+RADIUS;}
static int find_unique_candidate(Candidate*out){
    int found=0;Candidate last;
    for(int ia=0;ia<g_matches.na;ia++){
        Candidate c;zero_local(&c,sizeof(c));c.a=g_matches.a[ia];
        int nb=0;for(int i=0;i<g_matches.nb;i++)if(within(g_matches.b[i],c.a)){c.b=g_matches.b[i];nb++;}
        for(int i=0;i<g_matches.nc;i++)if(within(g_matches.c[i],c.a)&&c.nc<MAX_C)c.c[c.nc++]=g_matches.c[i];
        for(int i=0;i<g_matches.nd;i++)if(within(g_matches.d[i],c.a)&&c.nd<8)c.d[c.nd++]=g_matches.d[i];
        if(nb==1&&c.nc>=1&&c.nc<=2&&c.nd==5){last=c;if(++found>1)return -1;}
    }
    if(found==1){*out=last;return 1;}return 0;
}

static int safe_read4(const void*addr,unsigned char out[4]){SIZE_T got=0;return ReadProcessMemory(GetCurrentProcess(),addr,out,4,&got)&&got==4;}
static int add_patch(Patch*r,int*n,uptr a,const unsigned char*nv){if(*n>=32)return 0;r[*n].addr=(unsigned char*)a;if(!safe_read4(r[*n].addr,r[*n].oldv))return 0;r[*n].newv=nv;r[*n].written=0;(*n)++;return 1;}
static int safe_write4(Patch*p,const unsigned char*v){DWORD oldp=0,tmp=0;SIZE_T wrote=0;if(!VirtualProtect(p->addr,4,PAGE_READWRITE,&oldp))return 0;BOOL ok=WriteProcessMemory(GetCurrentProcess(),p->addr,v,4,&wrote);VirtualProtect(p->addr,4,oldp,&tmp);return ok&&wrote==4;}

static int apply_candidate(const Candidate*c){
    Patch r[32];int n=0;if(!add_patch(r,&n,c->a,NEW_732))return 0;if(!add_patch(r,&n,c->b,NEW_732))return 0;
    for(int i=0;i<c->nc;i++)if(!add_patch(r,&n,c->c[i],NEW_1440))return 0;for(int i=0;i<c->nd;i++)if(!add_patch(r,&n,c->d[i],NEW_1440))return 0;
    for(int i=0;i<n;i++){unsigned char now[4];const unsigned char*expect=i==0?PAT_A:(i==1?PAT_B:(i<2+c->nc?PAT_C:PAT_D));if(!safe_read4(r[i].addr,now)||!eq4(now,expect))return 0;}
    for(int i=0;i<n;i++){if(!safe_write4(&r[i],r[i].newv)){for(int j=0;j<i;j++)if(r[j].written)safe_write4(&r[j],r[j].oldv);return 0;}r[i].written=1;}
    for(int i=0;i<n;i++){unsigned char now[4];if(!safe_read4(r[i].addr,now)||!eq4(now,r[i].newv)){for(int j=0;j<n;j++)if(r[j].written)safe_write4(&r[j],r[j].oldv);return 0;}}
    return 1;
}

static DWORD WINAPI worker(LPVOID unused){
    (void)unused;log_line("TEST4 WORKER STARTED - GAME PROCESS ONLY");if(!verify_game()){log_line("FATAL: GAME BUILD GATE FAILED - ZERO PATCHES");return 0;}log_line("GAME BUILD GATE PASSED");
    Sleep(12000);log_line("SAFE MEMORY SCAN STARTED");
    for(int attempt=0;attempt<45;attempt++){
        int cr=collect_matches();if(cr<0){log_line("SAFE STOP: MATCH TABLE OVERFLOW - ZERO PATCHES");return 0;}if(cr==0){log_line("SAFE STOP: MEMORY BUFFER ALLOCATION FAILED - ZERO PATCHES");return 0;}
        Candidate c;int r=find_unique_candidate(&c);if(r<0){log_line("SAFE STOP: MULTIPLE INVENTORY CLUSTERS - ZERO PATCHES");return 0;}if(r==1){log_line("UNIQUE INVENTORY CLUSTER FOUND");if(apply_candidate(&c))log_line("SUCCESS: MAX INVENTORY APPLIED - 732 / 1440");else log_line("FATAL: PATCH FAILED OR ROLLED BACK");return 0;}Sleep(1000);
    }
    log_line("SAFE STOP: INVENTORY CLUSTER NOT PROVEN - ZERO PATCHES");return 0;
}
#endif

BOOL WINAPI DllMain(HINSTANCE h,DWORD reason,LPVOID reserved){
    (void)reserved;if(reason!=DLL_PROCESS_ATTACH)return TRUE;g_self=(HMODULE)h;DisableThreadLibraryCalls(h);
    if(!current_process_is_game())return TRUE;
    g_mutex=CreateMutexW(NULL,FALSE,L"Local\\CrimsonMaxInventory1561_CD20100_TEST4");if(!g_mutex)return TRUE;if(GetLastError()==ERROR_ALREADY_EXISTS)return TRUE;
    log_line("DLL_PROCESS_ATTACH OK - CRIMSONDESERT.EXE ONLY");
#ifdef PROBE_ONLY
    if(verify_game())log_line("TEST4 LOADER PROBE SUCCESS - GAME BUILD MATCHED");else log_line("TEST4 LOADER PROBE FAILED - BUILD MISMATCH");
#else
    HANDLE t=CreateThread(NULL,0,worker,NULL,0,NULL);if(t){CloseHandle(t);log_line("ONE WORKER THREAD CREATED");}else log_line("FATAL: WORKER THREAD CREATE FAILED");
#endif
    return TRUE;
}
