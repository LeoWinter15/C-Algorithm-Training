// Source: https://www.luogu.com.cn/article/7hd2fs5a
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
typedef pair<ll,int> pii;
pii operator+(pii a,pii b){
	return pii{a.first+b.first,a.second+b.second};
}
int n,k;
int h[N],e[N<<1],ne[N<<1],w[N<<1],tot,deg[N];
void add(int a,int b,int c){
	e[++tot]=b,ne[tot]=h[a],h[a]=tot,w[tot]=c;
}
pii dp[N][2];
int wqs_val;
ll dist[N];
void dfs(int x,int fa){
	for(int i=h[x];i;i=ne[i])if(e[i]!=fa){
		dist[e[i]]=dist[x]+w[i];
		dfs(e[i],x);
	}
}
void solve(int x,int fa){
	dp[x][0]={dist[x]+wqs_val,1};
	if(x!=1&&deg[x]==1){
		dp[x][1]={dist[x]+wqs_val,1};
		return;
	}
	dp[x][1]={0x3f3f3f3f3f3f3f3f,0};
	for(int i=h[x];i;i=ne[i])if(e[i]!=fa){
		solve(e[i],x);
		pii f0=dp[x][0],f1=dp[x][1];
		dp[x][0]=min(min(f0+dp[e[i]][1],f1+dp[e[i]][0]+pii{w[i],0}),f0+dp[e[i]][0]+pii{w[i]-dist[x]-wqs_val,-1});
		dp[x][1]=min(min(f1+dp[e[i]][1],f0+dp[e[i]][1]+pii{-dist[x]-wqs_val,-1}),f1+dp[e[i]][0]+pii{w[i]-dist[x]-wqs_val,-1});
	}
}
bool check(ll mid){
	wqs_val=mid;
	solve(1,0);
	return dp[1][1].second<=k;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1,a,b,c;i<n;i++)scanf("%d%d%d",&a,&b,&c),add(a,b,c),add(b,a,c),deg[a]++,deg[b]++;
	dfs(1,0);
	solve(1,0);
	if(dp[1][1].second<=k){
		printf("%lld\n",dp[1][1].first);
		return 0;
	}ll l=0,r=1e9,ans=-1;
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}check(ans);
	printf("%lld\n",dp[1][1].first-ans*k);
	return 0;
}
