// Source: https://www.luogu.com.cn/article/xxrrz7lf
#include<bits/stdc++.h>
#define int long long
#define N 505
using namespace std;
int n,m,u[N][N],d[N][N],x,y,die[N][N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)d[i][j]=n+1;
	}
	int ans=n*(n+1)/2*m*(m+1)/2;
	for(int i=1;i<=n*m;++i){
		cin>>x>>y;int up=1,down=n;
		for(int l=y;l>=1;--l){
			if(die[x][l])break;
			up=max(up,u[x][l]+1);down=min(down,d[x][l]-1);
			int up2=up,down2=down;
			for(int r=y;r<=m;++r){
				if(die[x][r])break;
				up2=max(up2,u[x][r]+1);down2=min(down2,d[x][r]-1);
				ans-=(down2-x+1)*(x-up2+1);
			}
		}
		cout<<ans<<'\n';die[x][y]=1;
		for(int j=x-1;j>=1;--j)d[j][y]=min(d[j][y],x);
		for(int j=x+1;j<=n;++j)u[j][y]=max(u[j][y],x);
	}
	return 0;
}
