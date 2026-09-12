#include<bits/stdc++.h>
using namespace std;
bool bg_memory;
chrono::_V2::system_clock::time_point bg_clock,en_clock;
void debugTime(){
    en_clock=chrono::high_resolution_clock::now();
    auto duration_clock=chrono::duration_cast<chrono::microseconds>(en_clock-bg_clock);
    double duration_count=duration_clock.count()*0.001;
    cerr<<"Time:"<<duration_count<<"ms"<<endl;
}
namespace GENSOKYO{
template<typename T>
void read(T &a){
    char c;a=0;int f=1;
    while(!isdigit(c=getchar()))if(c=='-')f=-1;
    do a=a*10+c-'0';
    while(isdigit(c=getchar()));
    a*=f;
}
template<typename T>
void write(T a){
    if(a<0)putchar('-'),a=-a;
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
char GC(){
    char c=getchar();
    while(c<=32)c=getchar();
    return c;
}
template<typename T1,typename T2>
void chmin(T1 &x,T2 y){if(x>y)x=y;}
template<typename T1,typename T2>
void chmax(T1 &x,T2 y){if(x<y)x=y;}
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> PII;
typedef pair<ll,int> PLI;
typedef __int128 lll;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
int RRand(int n){return (ull)rng()*n>>32;}
int RRand(int l,int r){return l+RRand(r-l+1);}
void gskinit(){
}
int n,m;
const int MAXN=1000010;
int p[MAXN],q[MAXN];

namespace SEG{
int mn[MAXN<<2],mx[MAXN<<2];
#define mid (L+R>>1)
void pushup(int x,int L,int R){
    mn[x]=min(mn[x<<1],mn[x<<1|1]);
    mx[x]=max(mx[x<<1],mx[x<<1|1]);
}
void build(int x,int L=1,int R=n){
    if(L==R){
        mn[x]=mx[x]=q[L];
    }else{
        build(x<<1,L,mid);
        build(x<<1|1,mid+1,R);
        pushup(x,L,R);
    }
}
void upd(int x,int pos,int L=1,int R=n){
    if(L==R){
        mn[x]=mx[x]=q[L];
    }else{
        if(pos<=mid)upd(x<<1,pos,L,mid);
        else upd(x<<1|1,pos,mid+1,R);
        pushup(x,L,R);
    }
}
int findR(int x,int l,int r,int L=1,int R=n){
    if(mn[x]>=l&&mx[x]<=r)return -1;
    if(L==R)return L;
    if(mn[x<<1]>=l&&mx[x<<1]<=r)return findR(x<<1|1,l,r,mid+1,R);
    else return findR(x<<1,l,r,L,mid);
}
#undef mid
}
namespace DS{
#define mid (L+R>>1)
struct Line{
    ll k,b;
    Line(){}
    Line(ll k,ll b):k(k),b(b){}
};
Line operator + (const Line A,const Line B){
    return Line(A.k+B.k,A.b+B.b);
}
Line operator * (const Line A,const ll B){
    return Line(A.k*B,A.b*B);
}
struct Node{
    int mx,mx2,mn,mn2,tagmx,tagmn;
    //  L's mx ; R's mn ;
    Line tag1,tag2,tag3,ansmn,ansmx;
    // no_ : with the other condition ; _ : no the other condition
    // for example get the mx but must not the mn ; get the mx but whether mn or not
}t[MAXN<<2];
void pushup(Node &A,Node &B,Node &C){
    // (A,B) -> C
    C.mx=max(A.mx,B.mx);
    C.mx2=max(A.mx==C.mx?A.mx2:A.mx,B.mx==C.mx?B.mx2:B.mx);
    C.mn=min(A.mn,B.mn);
    C.mn2=min(A.mn==C.mn?A.mn2:A.mn,B.mn==C.mn?B.mn2:B.mn);
}
void build(int x,int L=0,int R=m){
    if(L==R){
        t[x].mx=n;
        t[x].mx2=0;
        t[x].mn=1;
        t[x].mn2=n+1;
        t[x].ansmx=Line(n,0);
        t[x].ansmn=Line(1,0);
        t[x].tag3=Line(n,0);
    }else{
        build(x<<1,L,mid);
        build(x<<1|1,mid+1,R);
        pushup(t[x<<1],t[x<<1|1],t[x]);
    }
}
void pushtag1(int x,int v1,Line v2,int fl,Line tag1){
    t[x].mx+=v1;
    t[x].tagmx+=v1;
    t[x].ansmx=t[x].ansmx+v2;
    if(!fl)t[x].tag3=t[x].tag3+tag1*t[x].mn;
    t[x].tag1=t[x].tag1+tag1;
}
void pushtag2(int x,int v1,Line v2,int fl,Line tag2){
    t[x].mn+=v1;
    t[x].tagmn+=v1;
    t[x].ansmn=t[x].ansmn+v2;
    if(!fl)t[x].tag3=t[x].tag3+tag2*t[x].mx;
    t[x].tag2=t[x].tag2+tag2;
}
void pushdown(int x){
    int fl0,fl1;
    bool Tmx=t[x].tagmx||t[x].tag1.k||t[x].tag1.b;
    bool Tmn=t[x].tagmn||t[x].tag2.k||t[x].tag2.b;
    fl0=t[x<<1].mx+t[x].tagmx==t[x].mx,fl1=t[x<<1].mn+t[x].tagmn==t[x].mn;
    if(fl0&&Tmx)pushtag1(x<<1,t[x].tagmx,t[x].ansmx,fl1,t[x].tag1);
    if(fl1&&Tmn)pushtag2(x<<1,t[x].tagmn,t[x].ansmn,fl0,t[x].tag2);
    if(fl0&&fl1)t[x<<1].tag3=t[x<<1].tag3+t[x].tag3;

    fl0=t[x<<1|1].mx+t[x].tagmx==t[x].mx,fl1=t[x<<1|1].mn+t[x].tagmn==t[x].mn;
    if(fl0&&Tmx)pushtag1(x<<1|1,t[x].tagmx,t[x].ansmx,fl1,t[x].tag1);
    if(fl1&&Tmn)pushtag2(x<<1|1,t[x].tagmn,t[x].ansmn,fl0,t[x].tag2);
    if(fl0&&fl1)t[x<<1|1].tag3=t[x<<1|1].tag3+t[x].tag3;

    t[x].tagmn=t[x].tagmx=0;
    t[x].tag1=t[x].tag2=t[x].tag3=t[x].ansmn=t[x].ansmx=Line(0,0);
}
void updmn(int x,int l,int r,int v,int tim,int L=0,int R=m){
    if(t[x].mx<=v)return;
    if(l<=L&&R<=r&&v>t[x].mx2){
        pushtag1(x,v-t[x].mx,Line(1,-tim+1)*(v-t[x].mx),0,Line(1,-tim+1)*(v-t[x].mx));
    }else{
        pushdown(x);
        if(l<=mid)updmn(x<<1,l,r,v,tim,L,mid);
        if(r>mid)updmn(x<<1|1,l,r,v,tim,mid+1,R);
        pushup(t[x<<1],t[x<<1|1],t[x]);
    }
}
void updmx(int x,int l,int r,int v,int tim,int L=0,int R=m){
    if(t[x].mn>=v)return;
    if(l<=L&&R<=r&&v<t[x].mn2){
        pushtag2(x,v-t[x].mn,Line(1,-tim+1)*(v-t[x].mn),0,Line(1,-tim+1)*(v-t[x].mn));
    }else{
        pushdown(x);
        if(l<=mid)updmx(x<<1,l,r,v,tim,L,mid);
        if(r>mid)updmx(x<<1|1,l,r,v,tim,mid+1,R);
        pushup(t[x<<1],t[x<<1|1],t[x]);
    }
}
ll Qrysmn(int pos,int T){
    int x=1,L=0,R=m;
    while(L<R){
        pushdown(x);
        if(pos<=mid){
            x=x<<1;
            R=mid;
        }else{
            x=x<<1|1;
            L=mid+1;
        }
    }
    return t[x].ansmx.k*T+t[x].ansmx.b;
}
ll Qrysmx(int pos,int T){
    int x=1,L=0,R=m;
    while(L<R){
        pushdown(x);
        if(pos<=mid){
            x=x<<1;
            R=mid;
        }else{
            x=x<<1|1;
            L=mid+1;
        }
    }
    return t[x].ansmn.k*T+t[x].ansmn.b;
}
ll Qryss(int pos,int T){
    int x=1,L=0,R=m;
    while(L<R){
        pushdown(x);
        if(pos<=mid){
            x=x<<1;
            R=mid;
        }else{
            x=x<<1|1;
            L=mid+1;
        }
    }
    return t[x].tag3.k*T+t[x].tag3.b;
}
#undef mid
}
vector<pair<int,int>> c[MAXN];
ll oans[MAXN];int qop[MAXN],qx[MAXN],qy[MAXN];
vector<int> qs[MAXN];
void main(){
    read(n),read(m);
    for(int i=1;i<=n;++i)read(p[i]),p[i]++,q[p[i]]=i;
    SEG::build(1);
    for(int i=1;i<=n;++i)c[i].emplace_back(q[i],0);
    for(int i=1,op,x,y;i<=m;++i){
        read(op),read(x),read(y);
        qop[i]=op,qx[i]=x,qy[i]=y;
        if(op==1){
            if(x!=y){
                swap(p[x],p[y]);
                q[p[x]]=x;
                q[p[y]]=y;
                SEG::upd(1,p[x]);
                SEG::upd(1,p[y]);
                c[p[x]].emplace_back(x,i);
                c[p[y]].emplace_back(y,i);
            }
        }else{
            int L=n+1,R=0;
            int K=SEG::findR(1,x,y);
            K=K==-1?n:K-1;
            if(K>=1){
                qs[K].emplace_back(i);
                oans[i]+=(ll)(y+1)*(-x+1)*K;
            }
        }
    }
    DS::build(1);
    for(int i=1;i<=n;++i){
        c[i].emplace_back(-1,m+1);
        for(int j=0;j+1<c[i].size();++j){
            DS::updmn(1,c[i][j].second,c[i][j+1].second-1,c[i][j].first,i);
            DS::updmx(1,c[i][j].second,c[i][j+1].second-1,c[i][j].first,i);
        }
        for(auto x:qs[i]){
            oans[x]+=DS::Qrysmn(x,i)*(qy[x]+1)+DS::Qrysmx(x,i)*(qx[x]-1)-DS::Qryss(x,i);
        }
    }
    for(int i=1;i<=m;++i)if(qop[i]==2)write(oans[i]),putchar('\n');
}
}
bool en_memory;
signed main(){
    bg_clock=chrono::high_resolution_clock::now();
    GENSOKYO::gskinit();
    int T=1;//cin>>T;
    while(T--)GENSOKYO::main();
    debugTime();
    double memory_used=(&en_memory-&bg_memory)/1024.0/1024;
    cerr<<"Memory: "<<memory_used<<"MB"<<endl;
    return 0;
}