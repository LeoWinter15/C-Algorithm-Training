// Source: https://www.luogu.com.cn/article/u6rskdda
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int n;
struct P{
	int id,c,x;
}a[N];
inline bool cmp(P a1,P a2)
{
	return a1.x<a2.x;
}
int l[N],r[N];
int c[N],cnt,t,ans[N];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]={i,read(),read()};
	sort(a+1,a+n+1,cmp);
	c[++cnt]=1;
	for(int i=2;i<=n;i++)
	{
		if(a[c[1]].c==a[i].c)
			c[++cnt]=i;
		else
		{
			while(cnt)
				r[c[cnt]]=i,cnt--;
			c[++cnt]=i;
		}
	}
	cnt=0;
	c[++cnt]=n;
	for(int i=n-1;i>=1;i--)
	{
		if(a[c[1]].c==a[i].c)
			c[++cnt]=i;
		else
		{
			while(cnt)
				l[c[cnt]]=i,cnt--;
			c[++cnt]=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		t=INT_MAX;
		if(l[i])
			t=a[i].x-a[l[i]].x;
		if(r[i])
			t=min(t,a[r[i]].x-a[i].x);
		ans[a[i].id]=t;
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
