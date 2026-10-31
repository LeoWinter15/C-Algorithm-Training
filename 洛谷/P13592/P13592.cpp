// Source: https://www.luogu.com.cn/article/h6aj84qf
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

namespace kanade
{
	int read()
	{
		int ans=0,fs=1;
		char ch=getchar();
		while(ch<'0'||ch>'9')
		{
			if(ch=='-')fs=-1;
			ch=getchar();
		}
		while(ch>='0'&&ch<='9')
		{
			ans=ans*10+ch-'0';
			ch=getchar();
		}
		return ans*fs;
	}
	
	int A[2010][2010];
	
	struct edge
	{
		int to,ne;
	}e[2000010];
	int H[400010],ds[400010];
	int cnt=1;
	
	void add(int a,int b)
	{
		e[++cnt].to=b;
		e[cnt].ne=H[a];
		H[a]=cnt;
		ds[b]++;
	}
	
	int n,m;
	int D[400010],ANS[510][510];
	int g(int x,int y)
	{
		return (x-1)*m+y;
	}
	
	void P(int s,int o)
	{
		int y=(s-1)%m+1,x=(s-y)/m+1;
		ANS[x][y]=o; 
	}
	
	void topo()
	{
		int l=1,r=1;
		D[l]=1;
		while(l<=r)
		{
			int u=D[l];
			P(u,l),l++;
			for(int i=H[u];i;i=e[i].ne)
			{
				int v=e[i].to;
				ds[v]--;
				if(!ds[v])D[++r]=v;
			}
		}
	}
	
	char S[100010];

	int main()
	{
		n=read(),m=read();
		for(int i=1;i<n;i++)
		{
			scanf("%s",S+2);
			for(int j=2;j<=m;j++)
			{
				A[i][j]=S[j]-'0';
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<m;j++)
			{
				add(g(i,j),g(i,j+1));
			}
			if(i<n)add(g(i,1),g(i+1,1));
		}
		for(int i=1;i<n;i++)
		{
			int zt=0;
			for(int j=2;j<=m;j++)
			{
				if(A[i][j]==2)zt^=1;
				if(zt)add(g(i+1,j),g(i,j));
				else add(g(i,j),g(i+1,j));
				if(A[i][j]==1)
				{
					if(zt)add(g(i+1,j),g(i,j-1));
					else add(g(i,j),g(i+1,j-1));
				}
				if(A[i][j]==3)
				{
					if(zt)add(g(i,j-1),g(i+1,j));
					else add(g(i+1,j-1),g(i,j));
				}
				
			}
		}
		topo();
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cout<<ANS[i][j]<<' ';
			}
			cout<<'\n';
		} 
		return 0;
	}
}

int main()
{
	kanade::main();
	return 0;
}
