#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HMODULE g_self;

#define GAME_TIMESTAMP 0x6A998DC4u
#define GAME_SIZE_IMAGE 0x16F1F000u
#define RADIUS 0x20000u
#define MAX_REGION_SIZE (64ull*1024ull*1024ull)
#define MAX_A 8
#define MAX_B 8
#define MAX_C 8
#define MAX_D 24

static const unsigned char PAT_A[4]={0x32,0x00,0xF0,0x00};
static const unsigned char PAT_B[4]={0xF0,0x00,0xF0,0x00};
static const unsigned char PAT_C[4]={0xF0,0x00,0xE8,0x03};
static const unsigned char PAT_D[4]={0x0A,0x00,0xE8,0x03};
static const unsigned char NEW_732[4]={0xDC,0x02,0xDC,0x02};
static const unsigned char NEW_1440[4]={0xA0,0x05,0xA0,0x05};

static void bzero_local(void *dst, SIZE_T n){volatile unsigned char *d=(volatile unsigned char*)dst;for(SIZE_T i=0;i<n;i++)d[i]=0;}
static void bcopy_local(void *dst,const void *src,SIZE_T n){unsigned char*d=(unsigned char*)dst;const unsigned char*s=(const unsigned char*)src;for(SIZE_T i=0;i<n;i++)d[i]=s[i];}
static int eq4(const unsigned char*a,const unsigned char*b){return a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3];}

static void make_log_path(WCHAR *out,DWORD cap){
    DWORD n=GetModuleFileNameW(g_self,out,cap);if(!n||n>=cap){if(cap)out[0]=0;return;}
    DWORD dot=n;
    for(DWORD i=0;i<n;i++){if(out[i]==L'\\'||out[i]==L'/')dot=n;else if(out[i]==L'.')dot=i;}
    if(dot==n){if(n+4>=cap){out[0]=0;return;}dot=n;}
    out[dot+0]=L'.';out[dot+1]=L'l';out[dot+2]=L'o';out[dot+3]=L'g';out[dot+4]=0;
}
static DWORD astrlen_local(const char*s){DWORD n=0;while(s&&s[n])n++;return n;}
static void log_line(const char*s){
    WCHAR path[MAX_PATH*2];for(DWORD i=0;i<MAX_PATH*2;i++)path[i]=0;make_log_path(path,MAX_PATH*2);if(!path[0])return;
    HANDLE h=CreateFileW(path,FILE_APPEND_DATA,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);if(h==INVALID_HANDLE_VALUE)return;
    DWORD w=0,n=astrlen_local(s);WriteFile(h,s,n,&w,NULL);static const char crlf[2]={'\r','\n'};WriteFile(h,crlf,2,&w,NULL);CloseHandle(h);
}

static int verify_game(HMODULE game){
    if(!game)return 0;unsigned char*b=(unsigned char*)game;IMAGE_DOS_HEADER*d=(IMAGE_DOS_HEADER*)b;if(d->e_magic!=IMAGE_DOS_SIGNATURE)return 0;
    IMAGE_NT_HEADERS64*n=(IMAGE_NT_HEADERS64*)(b+d->e_lfanew);if(n->Signature!=IMAGE_NT_SIGNATURE)return 0;
    return n->FileHeader.TimeDateStamp==GAME_TIMESTAMP&&n->OptionalHeader.SizeOfImage==GAME_SIZE_IMAGE;
}

#ifndef PROBE_ONLY

typedef ULONG_PTR uptr;
typedef struct{uptr a[MAX_A];int na,oa;uptr b[MAX_B];int nb,ob;uptr c[MAX_C];int nc,oc;uptr d[MAX_D];int nd,od;uptr base;SIZE_T size;}Matches;
typedef struct{uptr anchor,lo,hi;uptr a[MAX_A];int na;uptr b[MAX_B];int nb;uptr c[MAX_C];int nc;uptr d[MAX_D];int nd;}Candidate;
typedef struct{unsigned char*addr;unsigned char oldv[4];const unsigned char*newv;int written;}Patch;

static void add_match(uptr*arr,int cap,int*n,int*overflow,uptr v){if(*n<cap)arr[(*n)++]=v;else *overflow=1;}
static int prot_ok(DWORD p){if(p&PAGE_GUARD)return 0;p&=0xff;return p==PAGE_READWRITE||p==PAGE_WRITECOPY||p==PAGE_READONLY;}
static void scan_region(const MEMORY_BASIC_INFORMATION*m,Matches*x){
    bzero_local(x,sizeof(*x));x->base=(uptr)m->BaseAddress;x->size=m->RegionSize;const unsigned char*p=(const unsigned char*)m->BaseAddress;SIZE_T n=m->RegionSize;
    for(SIZE_T i=0;i+4<=n;i++){
        if(p[i]==0x32&&eq4(p+i,PAT_A))add_match(x->a,MAX_A,&x->na,&x->oa,(uptr)(p+i));
        else if(p[i]==0xF0){if(eq4(p+i,PAT_B))add_match(x->b,MAX_B,&x->nb,&x->ob,(uptr)(p+i));else if(eq4(p+i,PAT_C))add_match(x->c,MAX_C,&x->nc,&x->oc,(uptr)(p+i));}
        else if(p[i]==0x0A&&eq4(p+i,PAT_D))add_match(x->d,MAX_D,&x->nd,&x->od,(uptr)(p+i));
    }
}
static int inwin(uptr p,uptr lo,uptr hi){return p>=lo&&p<=hi;}
static int build_candidate(const Matches*m,uptr anchor,Candidate*c){
    uptr end=m->base+m->size,lo=anchor>RADIUS?anchor-RADIUS:m->base,hi=anchor+RADIUS;if(lo<m->base)lo=m->base;if(hi>end)hi=end;bzero_local(c,sizeof(*c));c->anchor=anchor;c->lo=lo;c->hi=hi;
    for(int i=0;i<m->na;i++)if(inwin(m->a[i],lo,hi))c->a[c->na++]=m->a[i];
    for(int i=0;i<m->nb;i++)if(inwin(m->b[i],lo,hi))c->b[c->nb++]=m->b[i];
    for(int i=0;i<m->nc;i++)if(inwin(m->c[i],lo,hi))c->c[c->nc++]=m->c[i];
    for(int i=0;i<m->nd;i++)if(inwin(m->d[i],lo,hi))c->d[c->nd++]=m->d[i];
    return c->na==1&&c->nb==1&&c->nc>=1&&c->nc<=2&&c->nd==5;
}
static int find_cluster(Candidate*out){
    SYSTEM_INFO si;GetSystemInfo(&si);uptr addr=(uptr)si.lpMinimumApplicationAddress,maxa=(uptr)si.lpMaximumApplicationAddress;int count=0;Candidate last;
    while(addr<maxa){MEMORY_BASIC_INFORMATION m;SIZE_T got=VirtualQuery((LPCVOID)addr,&m,sizeof(m));if(!got)break;uptr next=(uptr)m.BaseAddress+m.RegionSize;if(next<=addr)break;
        if(m.State==MEM_COMMIT&&(m.Type==MEM_PRIVATE||m.Type==MEM_MAPPED)&&prot_ok(m.Protect)&&m.RegionSize>=4096&&m.RegionSize<=MAX_REGION_SIZE){Matches x;scan_region(&m,&x);if(!x.oa&&!x.ob&&!x.oc&&!x.od&&x.na){for(int i=0;i<x.na;i++){Candidate c;if(build_candidate(&x,x.a[i],&c)){last=c;if(++count>1)return -1;}}}}
        addr=next;
    }
    if(count==1){*out=last;return 1;}return 0;
}
static int add_patch(Patch*r,int*n,uptr a,const unsigned char*newv){if(*n>=32)return 0;r[*n].addr=(unsigned char*)a;for(int i=0;i<4;i++)r[*n].oldv[i]=r[*n].addr[i];r[*n].newv=newv;r[*n].written=0;(*n)++;return 1;}
static int apply_cluster(const Candidate*c){
    Patch r[32];int n=0;
    for(int i=0;i<c->na;i++)if(!add_patch(r,&n,c->a[i],NEW_732))return 0;
    for(int i=0;i<c->nb;i++)if(!add_patch(r,&n,c->b[i],NEW_732))return 0;
    for(int i=0;i<c->nc;i++)if(!add_patch(r,&n,c->c[i],NEW_1440))return 0;
    for(int i=0;i<c->nd;i++)if(!add_patch(r,&n,c->d[i],NEW_1440))return 0;
    for(int i=0;i<n;i++){const unsigned char*expect=i<c->na?PAT_A:(i<c->na+c->nb?PAT_B:(i<c->na+c->nb+c->nc?PAT_C:PAT_D));if(!eq4(r[i].addr,expect))return 0;}
    for(int i=0;i<n;i++){DWORD oldp,tmp;if(!VirtualProtect(r[i].addr,4,PAGE_READWRITE,&oldp)){for(int j=i-1;j>=0;j--){DWORD op,t;if(VirtualProtect(r[j].addr,4,PAGE_READWRITE,&op)){for(int k=0;k<4;k++)r[j].addr[k]=r[j].oldv[k];VirtualProtect(r[j].addr,4,op,&t);}}return 0;}for(int k=0;k<4;k++)r[i].addr[k]=r[i].newv[k];VirtualProtect(r[i].addr,4,oldp,&tmp);r[i].written=1;}
    for(int i=0;i<n;i++)if(!eq4(r[i].addr,r[i].newv)){for(int j=0;j<n;j++)if(r[j].written){DWORD op,t;if(VirtualProtect(r[j].addr,4,PAGE_READWRITE,&op)){for(int k=0;k<4;k++)r[j].addr[k]=r[j].oldv[k];VirtualProtect(r[j].addr,4,op,&t);}}return 0;}
    return 1;
}
static DWORD WINAPI worker(LPVOID unused){
    (void)unused;Sleep(8000);log_line("WORKER STARTED");HMODULE game=GetModuleHandleW(L"CrimsonDesert.exe");if(!verify_game(game)){log_line("FATAL: GAME BUILD GATE FAILED - ZERO PATCHES");return 0;}log_line("GAME BUILD GATE PASSED");
    for(int attempt=0;attempt<60;attempt++){Candidate c;int r=find_cluster(&c);if(r<0){log_line("SAFE STOP: MULTIPLE INVENTORY CLUSTERS - ZERO PATCHES");return 0;}if(r==1){log_line("UNIQUE INVENTORY CLUSTER FOUND");if(apply_cluster(&c))log_line("SUCCESS: MAX INVENTORY APPLIED - 732 / 1440");else log_line("FATAL: PATCH FAILED OR ROLLED BACK");return 0;}Sleep(1000);}log_line("SAFE STOP: INVENTORY CLUSTER NOT PROVEN - ZERO PATCHES");return 0;
}
#endif

BOOL WINAPI DllMain(HINSTANCE h,DWORD reason,LPVOID reserved){
    (void)reserved;
    if(reason==DLL_PROCESS_ATTACH){g_self=(HMODULE)h;DisableThreadLibraryCalls(h);log_line("DLL_PROCESS_ATTACH OK - FREESTANDING KERNEL32 ONLY");
#ifndef PROBE_ONLY
        HANDLE t=CreateThread(NULL,0,worker,NULL,0,NULL);if(t){CloseHandle(t);log_line("WORKER THREAD CREATED");}else log_line("FATAL: WORKER THREAD CREATE FAILED");
#else
        HMODULE game=GetModuleHandleW(L"CrimsonDesert.exe");if(verify_game(game))log_line("LOADER PROBE SUCCESS - GAME BUILD MATCHED");else log_line("LOADER PROBE LOADED - GAME BUILD DID NOT MATCH");
#endif
    }
    return TRUE;
}
