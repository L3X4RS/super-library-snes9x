#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static HMODULE g_self;
static volatile LONG g_started;
#define GAME_TIMESTAMP 0x6A998DC4u
#define GAME_SIZE_IMAGE 0x16F1F000u
#define MAX_A 8
#define MAX_B 8
#define MAX_C 8
#define MAX_D 24
#define CLUSTER_RADIUS 0x20000u
#define MAX_REGION_SIZE (64ull*1024ull*1024ull)

static const unsigned char PAT_A[4]={0x32,0x00,0xF0,0x00};
static const unsigned char PAT_B[4]={0xF0,0x00,0xF0,0x00};
static const unsigned char PAT_C[4]={0xF0,0x00,0xE8,0x03};
static const unsigned char PAT_D[4]={0x0A,0x00,0xE8,0x03};
static const unsigned char NEW_732[4]={0xDC,0x02,0xDC,0x02};
static const unsigned char NEW_1440[4]={0xA0,0x05,0xA0,0x05};

#ifndef NO_LOG
static void log_path(WCHAR *out,DWORD cap){
    DWORD n=GetModuleFileNameW(g_self,out,cap); if(!n||n>=cap)return;
    WCHAR *dot=NULL; for(DWORD i=0;i<n;i++){if(out[i]==L'\\'||out[i]==L'/')dot=NULL; else if(out[i]==L'.')dot=&out[i];}
    if(!dot)dot=out+n; const WCHAR ext[]=L".log"; if((size_t)(cap-(dot-out))>=sizeof(ext)/sizeof(ext[0]))memcpy(dot,ext,sizeof(ext));
}
static void log_msg(const char *fmt,...){
    char b[2048]; va_list ap; va_start(ap,fmt); int n=vsnprintf(b,sizeof(b)-3,fmt,ap); va_end(ap); if(n<0)return; if(n>(int)sizeof(b)-3)n=(int)sizeof(b)-3; b[n++]='\r';b[n++]='\n';b[n]=0;
    WCHAR p[MAX_PATH*2]={0}; log_path(p,(DWORD)(sizeof(p)/sizeof(p[0]))); if(!p[0])return;
    HANDLE h=CreateFileW(p,FILE_APPEND_DATA,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); if(h==INVALID_HANDLE_VALUE)return; DWORD w;WriteFile(h,b,(DWORD)n,&w,NULL);CloseHandle(h);
}
#else
#define log_msg(...) ((void)0)
#endif

typedef struct{uintptr_t a[MAX_A];int na,oa;uintptr_t b[MAX_B];int nb,ob;uintptr_t c[MAX_C];int nc,oc;uintptr_t d[MAX_D];int nd,od;uintptr_t base;SIZE_T size;}Matches;
typedef struct{uintptr_t anchor,lo,hi;uintptr_t a[MAX_A];int na;uintptr_t b[MAX_B];int nb;uintptr_t c[MAX_C];int nc;uintptr_t d[MAX_D];int nd;}Candidate;
typedef struct{unsigned char *addr,oldv[4],newv[4];int written;}Patch;
static int eq4(const unsigned char*p,const unsigned char*q){return p[0]==q[0]&&p[1]==q[1]&&p[2]==q[2]&&p[3]==q[3];}
static void add(uintptr_t*a,int cap,int*n,int*o,uintptr_t v){if(*n<cap)a[(*n)++]=v;else *o=1;}
static int prot_ok(DWORD p,int broad){if(p&PAGE_GUARD)return 0;p&=0xff;if(p==PAGE_READWRITE||p==PAGE_WRITECOPY)return 1;return broad&&p==PAGE_READONLY;}
static void scan_region(const MEMORY_BASIC_INFORMATION*m,Matches*x){
    memset(x,0,sizeof(*x));x->base=(uintptr_t)m->BaseAddress;x->size=m->RegionSize;const unsigned char*p=(const unsigned char*)m->BaseAddress;SIZE_T n=m->RegionSize;
    for(SIZE_T i=0;i+4<=n;i++){if(p[i]==0x32&&eq4(p+i,PAT_A))add(x->a,MAX_A,&x->na,&x->oa,(uintptr_t)(p+i));else if(p[i]==0xF0){if(eq4(p+i,PAT_B))add(x->b,MAX_B,&x->nb,&x->ob,(uintptr_t)(p+i));else if(eq4(p+i,PAT_C))add(x->c,MAX_C,&x->nc,&x->oc,(uintptr_t)(p+i));}else if(p[i]==0x0A&&eq4(p+i,PAT_D))add(x->d,MAX_D,&x->nd,&x->od,(uintptr_t)(p+i));}
}
static int inside(uintptr_t p,uintptr_t lo,uintptr_t hi){return p>=lo&&p<=hi;}
static int candidate(const Matches*m,uintptr_t anchor,Candidate*c){
    uintptr_t end=m->base+m->size,lo=anchor>CLUSTER_RADIUS?anchor-CLUSTER_RADIUS:m->base,hi=anchor+CLUSTER_RADIUS;if(lo<m->base)lo=m->base;if(hi>end)hi=end;memset(c,0,sizeof(*c));c->anchor=anchor;c->lo=lo;c->hi=hi;
    for(int i=0;i<m->na;i++)if(inside(m->a[i],lo,hi))c->a[c->na++]=m->a[i];for(int i=0;i<m->nb;i++)if(inside(m->b[i],lo,hi))c->b[c->nb++]=m->b[i];for(int i=0;i<m->nc;i++)if(inside(m->c[i],lo,hi))c->c[c->nc++]=m->c[i];for(int i=0;i<m->nd;i++)if(inside(m->d[i],lo,hi))c->d[c->nd++]=m->d[i];
    return c->na==1&&c->nb==1&&c->nc>=1&&c->nc<=2&&c->nd==5;
}
static int find_cluster(Candidate*out,int broad){
    SYSTEM_INFO si;GetSystemInfo(&si);uintptr_t a=(uintptr_t)si.lpMinimumApplicationAddress,max=(uintptr_t)si.lpMaximumApplicationAddress;int count=0;Candidate last;
    while(a<max){MEMORY_BASIC_INFORMATION m;if(!VirtualQuery((LPCVOID)a,&m,sizeof(m)))break;uintptr_t next=(uintptr_t)m.BaseAddress+m.RegionSize;if(next<=a)break;int type=(m.Type==MEM_PRIVATE||m.Type==MEM_MAPPED||(broad&&m.Type==MEM_IMAGE));if(m.State==MEM_COMMIT&&type&&prot_ok(m.Protect,broad)&&m.RegionSize>=4096&&m.RegionSize<=MAX_REGION_SIZE){Matches x;scan_region(&m,&x);if(!x.oa&&!x.ob&&!x.oc&&!x.od&&x.na){for(int i=0;i<x.na;i++){Candidate c;if(candidate(&x,x.a[i],&c)){last=c;if(++count>1)return -1;}}}}a=next;}
    if(count==1){*out=last;return 1;}return 0;
}
static int add_patch(Patch*r,int*n,uintptr_t a,const unsigned char*v){if(*n>=32)return 0;r[*n].addr=(unsigned char*)a;memcpy(r[*n].oldv,r[*n].addr,4);memcpy(r[*n].newv,v,4);r[*n].written=0;(*n)++;return 1;}
static int apply(const Candidate*c){
    Patch r[32];int n=0;for(int i=0;i<c->na;i++)if(!add_patch(r,&n,c->a[i],NEW_732))return 0;for(int i=0;i<c->nb;i++)if(!add_patch(r,&n,c->b[i],NEW_732))return 0;for(int i=0;i<c->nc;i++)if(!add_patch(r,&n,c->c[i],NEW_1440))return 0;for(int i=0;i<c->nd;i++)if(!add_patch(r,&n,c->d[i],NEW_1440))return 0;
    for(int i=0;i<n;i++){const unsigned char*e=i<c->na?PAT_A:i<c->na+c->nb?PAT_B:i<c->na+c->nb+c->nc?PAT_C:PAT_D;if(!eq4(r[i].addr,e)){log_msg("SAFE STOP: candidate changed before write at %p",r[i].addr);return 0;}}
    for(int i=0;i<n;i++){DWORD oldp,tmp;if(!VirtualProtect(r[i].addr,4,PAGE_READWRITE,&oldp)){for(int j=i-1;j>=0;j--){DWORD op,t;if(VirtualProtect(r[j].addr,4,PAGE_READWRITE,&op)){memcpy(r[j].addr,r[j].oldv,4);VirtualProtect(r[j].addr,4,op,&t);}}return 0;}memcpy(r[i].addr,r[i].newv,4);VirtualProtect(r[i].addr,4,oldp,&tmp);r[i].written=1;}
    for(int i=0;i<n;i++)if(!eq4(r[i].addr,r[i].newv)){for(int j=0;j<n;j++)if(r[j].written){DWORD op,t;if(VirtualProtect(r[j].addr,4,PAGE_READWRITE,&op)){memcpy(r[j].addr,r[j].oldv,4);VirtualProtect(r[j].addr,4,op,&t);}}return 0;}
    log_msg("SUCCESS: Backpack/Kuku=732; Private/Wardrobe/Cooler/Gatherables/Collectibles/Symbol=1440. Records=%d",n);return 1;
}
static int build_ok(HMODULE game){unsigned char*b=(unsigned char*)game;IMAGE_DOS_HEADER*d=(IMAGE_DOS_HEADER*)b;if(d->e_magic!=IMAGE_DOS_SIGNATURE)return 0;IMAGE_NT_HEADERS64*n=(IMAGE_NT_HEADERS64*)(b+d->e_lfanew);if(n->Signature!=IMAGE_NT_SIGNATURE)return 0;log_msg("Game module=%p timestamp=0x%08lX SizeOfImage=0x%08lX",game,(unsigned long)n->FileHeader.TimeDateStamp,(unsigned long)n->OptionalHeader.SizeOfImage);return n->FileHeader.TimeDateStamp==GAME_TIMESTAMP&&n->OptionalHeader.SizeOfImage==GAME_SIZE_IMAGE;}
static DWORD WINAPI worker(LPVOID u){
    (void)u;log_msg("============================================================");log_msg("CRIMSON MAX INVENTORY 1561 - CD 2.01.00 - TEST2");log_msg("Worker thread; no PAZ/PAMT writes; fail-closed semantic runtime scan.");log_msg("============================================================");
    HMODULE game=NULL;for(int i=0;i<100&&!game;i++){game=GetModuleHandleW(L"CrimsonDesert.exe");if(!game)Sleep(50);}if(!game){log_msg("FATAL: CrimsonDesert.exe not found. ZERO PATCHES.");return 0;}if(!build_ok(game)){log_msg("FATAL: unsupported game build. ZERO PATCHES.");return 0;}log_msg("Build gate passed. Waiting for inventory.staticinfobody-derived runtime cluster...");
    for(int i=0;i<120;i++){Candidate c;int r=find_cluster(&c,i>=30);if(r<0){log_msg("SAFE STOP: multiple semantic clusters. ZERO PATCHES.");return 0;}if(r==1){log_msg("Unique cluster anchor=%p A=%d B=%d C=%d D=%d",(void*)c.anchor,c.na,c.nb,c.nc,c.nd);if(!apply(&c))log_msg("FATAL: transaction failed/rolled back.");return 0;}Sleep(i<30?500:1000);}log_msg("SAFE STOP: cluster not proven. ZERO PATCHES.");return 0;
}
BOOL WINAPI DllMain(HINSTANCE h,DWORD reason,LPVOID r){(void)r;if(reason==DLL_PROCESS_ATTACH){g_self=(HMODULE)h;DisableThreadLibraryCalls(h);if(InterlockedCompareExchange(&g_started,1,0)==0){HANDLE t=CreateThread(NULL,0,worker,NULL,0,NULL);if(t)CloseHandle(t);}}return TRUE;}
