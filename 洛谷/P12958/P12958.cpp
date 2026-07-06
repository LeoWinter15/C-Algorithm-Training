#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
typedef long long ll;
int T,n,k,s[N],dfn[N],dn,low[N],id[N],lsh[N],ct,t;
ll val[N<<1];
vector<int>lk[N];
//y,coef,id,part
vector<array<int,4>>q[N];
void add(int x,int v){
    for(;x<=ct;x+=x&-x)val[x]+=v;
}
ll query(int x){
    ll res=0;
    for(;x;x-=x&-x)res+=val[x];
    return res;
}
void D1(int u){
    dfn[u]=++dn,id[dn]=u;
    for(int v:lk[u])D1(v);
    low[u]=dn;
}
void D2(int u){
    int x=lower_bound(lsh+1,lsh+1+t,(s[u]-1)/k)-lsh;
    q[dfn[u]-1].push_back({x,-1,u,0});
    q[low[u]].push_back({x,1,u,0});
    q[dfn[u]-1].push_back({x,1,u,1});
    q[low[u]].push_back({x,-1,u,1});
    q[n].push_back({x,1,u,1});
    for(int v:lk[u])D2(v);
}
int main(){
    cin>>T;
    for(int c=1;c<=T;c++){
        cin>>n>>k;ct=dn=0;memset(val,0,sizeof(val));
        for(int i=1;i<=n;i++)cin>>s[i],lk[i].clear(),q[i].clear();
        for(int i=1;i<=n;i++)lsh[++ct]=s[i],lsh[++ct]=(s[i]-1)/k;
        sort(lsh+1,lsh+1+ct);
        t=unique(lsh+1,lsh+1+ct)-lsh-1;
        for(int i=2,f;i<=n;i++)cin>>f,lk[f].push_back(i);
        D1(1),D2(1);vector<vector<ll>>ans(n+1,vector<ll>(2,0));
        for(int i=1;i<=n;i++){
            add(lower_bound(lsh+1,lsh+1+t,s[id[i]])-lsh,1);
            for(auto [y,coef,u,part]:q[i])ans[u][part]+=coef*query(y);
        }
        ll res=0;
        for(int i=1;i<=n;i++)res+=ans[i][0]*ans[i][1];
        cout<<"Case #"<<c<<": "<<res<<'\n';
    }

    return 0;
}
