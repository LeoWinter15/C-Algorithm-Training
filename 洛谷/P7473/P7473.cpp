// Source: https://www.luogu.com.cn/article/k3cmm8i0
#include<bits/stdc++.h>
using namespace std;
const int N=305,M=2005,MN=1e5+5;
struct edge{
	int to,nxt;
}e[MN];
int a[N][N],dis[M][M],id[N][N],t[M][M][4];
int n,m,Q,cnt,head[M][4],tot;
inline void add(int u,int v,int p){
	e[++cnt].to=v;
	e[cnt].nxt=head[u][p];
	head[u][p]=cnt;
}
inline bool check(int i,int j){
	if(a[i-1][j]||a[i+1][j]||a[i][j-1]||a[i][j+1]) return true;
	return false;
}
inline int getans(int X1,int Y1,int X2,int Y2){
	return min(dis[t[X1][Y1][0]][t[X2][Y2][0]],min(dis[t[X1][Y1][1]][t[X2][Y2][1]],min(dis[t[X1][Y1][2]][t[X2][Y2][2]],dis[t[X1][Y1][3]][t[X2][Y2][3]])));
}
queue<pair<int,int> > q;
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		a[x][y]=1;
	}
	for(int i=1;i<=n;i++) a[0][i]=a[n+1][i]=a[i][0]=a[i][n+1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!a[i][j]&&check(i,j)) id[i][j]=++tot;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) 
			t[i][j][0]=a[i][j-1]?id[i][j]:t[i][j-1][0],
			t[i][j][1]=a[i-1][j]?id[i][j]:t[i-1][j][1];
	for(int i=n;i;i--)
		for(int j=n;j;j--)
			t[i][j][2]=a[i][j+1]?id[i][j]:t[i][j+1][2],
			t[i][j][3]=a[i+1][j]?id[i][j]:t[i+1][j][3];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(id[i][j]) for(int k=0;k<=3;k++) add(t[i][j][k],id[i][j],k);
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
			dis[i][j]=1e9+7;
	for(int i=1;i<=tot;i++) q.push(make_pair(i,i)),dis[i][i]=1;
	while(!q.empty()){
		pair<int,int> x=q.front();q.pop();
		for(int k=0;k<=3;k++){
			for(int i=head[x.first][k];i;i=e[i].nxt){
				for(int j=head[x.second][k];j;j=e[j].nxt){
					int u=e[i].to,v=e[j].to;
					if(dis[u][v]==1e9+7){
						dis[u][v]=dis[x.first][x.second]+1,
						q.push(make_pair(u,v));
					}
				}
			}
		}
	}
	for(int i=1,X1,X2,Y1,Y2;i<=Q;i++){
		scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
		if(X1==X2&&Y1==Y2) printf("0\n");
		else{
			int ans=getans(X1,Y1,X2,Y2);
			if(ans>=1e9) printf("-1\n");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
