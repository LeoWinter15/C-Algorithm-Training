# include <stdio.h>
# include <algorithm>
# define int long long
int a[1010][1010];
int ff[1010],f[1010],z[1010],bj[1010],hzh[1010],ok[1010];
int anss=1;
int mod=1000000007;
void done(int x,int y)
{
	int p=x,q=y;
	anss*=(a[p][q+1]>a[x][y])+(a[p+1][q]>a[x][y])+(a[p-1][q]>=a[x][y])+(a[p][q-1]>=a[x][y]);
	anss%=mod;
	return;
}
void gx(int x,int y)
{
	int p=x,q=y;
	hzh[a[x][y]]+=(a[p][q+1]>a[x][y])+(a[p+1][q]>a[x][y])+(a[p-1][q]>a[x][y])+(a[p][q-1]>a[x][y]);
	return;
}
int pan(int x,int y)
{
	int p=x,q=y;
	if(a[p][q+1]==a[x][y] || a[p+1][q]==a[x][y] || a[p-1][q]==a[x][y] || a[p][q-1]==a[x][y])
		return 1;
	else
		return 0;
}
int read()
{
	int now=0;
	char c=getchar();
	while(c<'0' || c>'9')
		c=getchar();
	while(c>='0' && c<='9')
	{
		now=(now<<1)+(now<<3)+(c&15);
		c=getchar();
	}
	return now;
}
signed main()
{
	int i,j,n,m,k,l,r,t,x,y,mx=0;
	t=read();
	while(t--)
	{
		n=read();
		m=read();
		k=read();
		l=read();
		r=read();
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				x=read();
				if(!bj[x] && x)
				{
					bj[x]=1;
					mx++;
				}
				else
				{
					bj[x]++;
					if(bj[x]>2 && x)
						while(1){}
				}
				a[i][j]=x;
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				if(!a[i][j])
					continue;
				if(ok[a[i][j]])
					continue;
				if(pan(i,j))
				{
					gx(i,j);
					if(a[i-1][j]==a[i][j])
						gx(i-1,j);
					if(a[i+1][j]==a[i][j])
						gx(i+1,j);
					if(a[i][j-1]==a[i][j])
						gx(i,j-1);
					if(a[i][j+1]==a[i][j])
						gx(i,j+1);
					hzh[a[i][j]]++;
					ok[a[i][j]]=1;
					continue;
				}
				if(bj[a[i][j]]>=2) while(1){}
				done(i,j);
				gx(i,j);
			}
		}
		f[mx]=anss;
		for(i=1000;i>=1;i--)
		{
			hzh[i]+=hzh[i+1];
			hzh[i]%=mod;
		}
		for(i=1;i<=1000;i++)
		{
			if(bj[i] || i>k)
				continue;
			ff[i]=hzh[i+1];
			for(j=2;j<=1000;j++)
			{
				z[j]=f[j-1]*ff[i];
				z[j]%=mod;
			}
			for(j=2;j<=1000;j++)
			{
				f[j]+=z[j];
				f[j]%=mod;
				z[j]=0;
			}
		}
		anss=0;
		for(i=l;i<=r;i++)
		{
			anss+=f[i];
			anss%=mod;
		}
		printf("%lld\n",anss);
		anss=1;
		mx=0;
		for(i=1;i<=1000;i++)
		{
			f[i]=0;
			z[i]=0;
			ff[i]=0;
			bj[i]=0;
			hzh[i]=0;
			ok[i]=0;
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
				a[i][j]=0;
		}
	}
	return 0;
}

