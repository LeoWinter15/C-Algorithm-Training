// Source: https://www.luogu.com.cn/article/yl6hcfnw
#include<bits/stdc++.h>
using namespace std;
const int szl=1e5+5,inf=0x3f3f3f3f;
int n,m;
vector<int> ed[szl],rbt[szl<<1];
int dfn[szl],low[szl],num,a[szl],f[szl][2];
int fa[szl],ext,dp[szl<<1][2];
void Solve(int u,int v){
	++ext;
	for(int i=v;i!=fa[u];i=fa[i]){
		rbt[ext].push_back(i);
		rbt[i].push_back(ext);
	}
	return;
}
void Tarjan(int x){
	dfn[x]=low[x]=++num;
	for(int y:ed[x]){
		if(y==fa[x])continue;
		if(!dfn[y]){
			fa[y]=x;
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}else low[x]=min(low[x],dfn[y]);
		if(low[y]<=dfn[x])continue;
		rbt[x].push_back(y);
		rbt[y].push_back(x);
	}
	for(int y:ed[x])if(fa[y]!=x&&dfn[y]>dfn[x])Solve(x,y);
}
//树形DP
void DP(int x,int f){
	if(x<=n){
		for(int y:rbt[x]){
			if(y==f)continue;
			DP(y,x);
			dp[x][0]+=max(dp[y][0],dp[y][1]);
			dp[x][1]+=dp[y][0];
		}
		dp[x][1]+=a[x];
	}else{
		for(int y:rbt[x]){
			if(y==f)continue;
			DP(y,x);
			dp[x][0]+=dp[y][0];	
		}
		for(int y:rbt[x]){
			if(y==f)continue;
			dp[x][1]=max(dp[x][1],dp[x][0]-dp[y][0]+dp[y][1]);
		}
	}
	return;
}
//环形DP
inline int Must(int x){
	f[0][0]=-inf,f[0][1]=dp[rbt[x][0]][1];
	for(int j=1;j<rbt[x].size();j++){
		f[j][0]=max(f[j-1][1],f[j-1][0])+dp[rbt[x][j]][0],
		f[j][1]=f[j-1][0]+dp[rbt[x][j]][1];
	}
	return f[rbt[x].size()-1][0];
}
inline int Mustnt(int x){
	memset(f,0,sizeof f);
	f[0][0]=dp[rbt[x][0]][0],f[0][1]=-inf;
	for(int j=1;j<rbt[x].size();j++){
		f[j][0]=max(f[j-1][1],f[j-1][0])+dp[rbt[x][j]][0],
		f[j][1]=f[j-1][0]+dp[rbt[x][j]][1];
	}
	return max(f[rbt[x].size()-1][0],f[rbt[x].size()-1][1]);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	ext=n;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		ed[u].push_back(v);
		ed[v].push_back(u);
	}
	for(int i=1;i<=n;i++)cin>>a[i];
	Tarjan(1);
	for(int i=n+1;i<=ext;i++){
		if(rbt[i].size()>3){
			for(int y:rbt[i])DP(y,i);
			cout<<max(Must(i),Mustnt(i));
			return 0;
		}
	}
	//没有特别的大环，可以直接树形DP
	DP(1,0);
	cout<<max(dp[1][0],dp[1][1]);		
	return 0;
}
