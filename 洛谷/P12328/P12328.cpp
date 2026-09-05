#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
int n , m , a[maxn][maxn] , b[maxn][maxn] , c[maxn][maxn] , dir[4][2]={{0 , 1} , {0 , -1} , {1 , 0} , {-1 , 0}} , sum , ans;
bool vis[maxn][maxn];
void Dfs(int x , int y)
{
	vis[x][y]=1;
	sum++;
	for (int i = 0; i < 4; i++)
	{
		int dx = x + dir[i][0] , dy = y + dir[i][1];
		if (vis[dx][dy] ^ 1 && c[dx][dy])Dfs(dx , dy);
	}
	return;
}
void Clear()
{
	for (int i = 200; i <= 301; i++) for (int j = m + 1; j <= 301; j++)c[i][j]=0;
	return;
}
void Work()
{
	for (int i = 200; i <= 301; i++) for (int j = 200; j <= 301; j++)vis[i][j]=0;
	for (int i = 200; i <= 301; i++) for (int j = 200; j <= 301; j++,sum=0) if ((vis[i][j] ^ 1) && c[i][j])Dfs(i , j),ans=max(ans , sum);
	return;
}
void debug()
{
	for (int i = 1; i <= n*2; i++) 
	{
		for (int j = 1; j <= n*2; j++) cout << c[200+i][200+j] << " ";
		cout << endl;
	}
}
void Turn(int st)
{
	Clear();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 - st + i][m + j] = b[i][j];
	Work();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 - st + i][m + j] = b[j][n - i + 1];
	Work();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 - st + i][m + j] = b[n - i + 1][n - j + 1];
	Work();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 - st + i][m + j] = b[n - j + 1][i];
	Work();
	return;
}
int main ()
{
	scanf("%d" , &n);
	m = 200 + n;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)scanf("%d" , &a[i][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)scanf("%d" , &b[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 + i][200 + j] = a[i][j];
	for (int i = -n-1; i <= n+1; i++)Turn(i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 + i][200 + j] = a[j][n - i + 1];
	for (int i = -n-1; i <= n+1; i++)Turn(i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 + i][200 + j] = a[n - i + 1][n - j + 1];
	for (int i = -n-1; i <= n+1; i++)Turn(i);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[200 + i][200 + j] = a[n - j + 1][i];
	for (int i = -n-1; i <= n+1; i++)Turn(i);
	printf("%d\n" , ans);
	return 0;
}
