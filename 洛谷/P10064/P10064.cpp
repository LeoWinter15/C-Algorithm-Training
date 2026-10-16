// Source: https://www.luogu.com.cn/article/8pcg7ujz
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=3e3+5;
const int MOD=998244353;
void add(ll &x,ll y){x=(x+y%MOD+MOD)%MOD;}
ll ksm(ll a,int b){ll r=1;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD,b>>=1;}return r;}
int n;
ll fac[MAXN],inf[MAXN],ans;
vector<int> edg[MAXN];
ll f[MAXN],g[MAXN];
int lef[MAXN],siz[MAXN],rt=1,sl=0;
ll C(int x,int y){return fac[y]*inf[x]%MOD*inf[y-x]%MOD;}
void dfs(int u,int fa){
	if(edg[u].size()==1){
		lef[u]=siz[u]=1;
		return;
	}
	for(int v:edg[u]) if(v!=fa) dfs(v,u);
	memset(f,0,sizeof(f));
	siz[u]=f[0]=1;
	int in=0;
	for(int v:edg[u]) if(v!=fa){
		memset(g,0,sizeof(g));
		for(int i=0;i<=lef[u];i++) for(int j=0;j<=lef[v];j++)
			add(g[i+j],f[i]*(j&1?MOD-1:1)%MOD*C(j,lef[v])%MOD*ksm(2,(siz[u]-i)*(siz[v]-j))%MOD);
		swap(f,g);
		siz[u]+=siz[v];lef[u]+=lef[v];in+=siz[v]*(siz[v]-1)/2;
	}
	int os=n-siz[u],of=sl-lef[u];in+=os*(os-1)/2;
	for(int i=0;i<=lef[u];i++) add(ans,f[i]*ksm(2,in)%MOD*ksm(2,(os-of)*(siz[u]-i))%MOD*ksm(ksm(2,siz[u]-i)-1,of)%MOD);
	if(fa){
		in=os*(os-1)/2+siz[u]*(siz[u]-1)/2;
		for(int i=0;i<=lef[u];i++) add(ans,(i&1?1:MOD-1)*C(i,lef[u])%MOD*ksm(2,in)%MOD*ksm(2,(siz[u]-i)*(os-of))%MOD*ksm(ksm(2,siz[u]-i)-1,of)%MOD);
	}
}
int main(){
	ios::sync_with_stdio(false);
	fac[0]=inf[0]=1;
	for(int i=1;i<MAXN;i++) inf[i]=ksm(fac[i]=fac[i-1]*i%MOD,MOD-2);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		edg[u].push_back(v);
		edg[v].push_back(u);
	}
	if(n==2) return cout<<1<<endl,0;
	while(edg[rt].size()==1) rt++;
	for(int i=1;i<=n;i++) if(edg[i].size()==1) sl++;
	dfs(rt,0);
	cout<<ans<<endl;
	return 0;
}
