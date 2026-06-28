#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,V=1e4;
typedef long long ll;
int n,a,b,c[N],dp[N],cv,tr[N];
vector<int>e[N];
ll f[N],ans;
struct line{
	ll a,b;
}va[N<<1];
inline ll W(int u,int x){
	return 1ll*va[u].a*x+va[u].b;
}
void ins(int k,int l,int r,int x){
	if(!tr[k]||W(tr[k],l)<=W(x,l)&&W(tr[k],r)<=W(x,r))return tr[k]=x,void();
	if(W(tr[k],l)>=W(x,l)&&W(tr[k],r)>=W(x,r))return;
	int mid=l+r>>1;
	if(W(tr[k],mid)<W(x,mid))swap(tr[k],x);
	if(W(tr[k],l)<W(x,l))ins(k<<1,l,mid,x);
	else ins(k<<1|1,mid+1,r,x);
}
ll query(int k,int l,int r,int x){
	if(!tr[k])return 0;
	int mid=l+r>>1;
	if(x<=mid)return max(W(tr[k],x),query(k<<1,l,mid,x));
	else return max(W(tr[k],x),query(k<<1|1,mid+1,r,x));
}
void add(int x){
	va[++cv]={-1ll*(dp[x]+1)*a,f[x]};
	ins(1,0,V,cv);
}
void dfs(int x){
	ans+=1ll*dp[x]*a*c[x];
	f[x]=max(f[x],query(1,0,V,c[x])+(1ll*dp[x]*a-b)*c[x]);
	add(x);
	for(auto v:e[x]){
		dp[v]=dp[x]+1;
		dfs(v);
		if(f[v]>f[x])f[x]=f[v],add(x);
	}
}
int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1,x,y;i<=n;++i){
		scanf("%d%d",&c[i],&x);
		while(x--){
			scanf("%d",&y);
			e[i].push_back(y);
		}
	}
	dfs(1);
	printf("%lld\n",ans-f[1]);
	return 0;
}
