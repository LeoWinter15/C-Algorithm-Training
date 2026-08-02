#include<bits/stdc++.h>
#define check(i,j) (abs(a[i].x-b[j].x)<=k)
//判断第 i 头 H 牛能否与第 j 头 G 牛匹配 
using namespace std;
struct cow{
	int x,v;
};
int t,n,k,cnt1,cnt2;
int na[5010],nb[5010],g[5010][5010],f[5010][5010][2];
cow a[5010],b[5010];
void init(){
	for(int i=1,j=1;i<=cnt1;i++)
	{
		while(j<=cnt2&&(check(i,j)||b[j].x<a[i].x))
			j+=1;
		nb[i]=j;
	}
	//预处理离第 i 头 H 牛最近的失配 G 牛的位置 
	for(int i=1,j=1;j<=cnt2;j++)
	{
		while(i<=cnt1&&(check(i,j)||a[i].x<b[j].x))
			i+=1;
		na[j]=i;
	}
	//预处理离第 j 头 G 牛最近的失配 H 牛的位置 
	na[0]=nb[0]=1;
	for(int i=cnt1;i>=1;i--)
	{
		for(int j=cnt2;j>=1;j--)
			if(check(i,j))g[i][j]=g[i+1][j+1]+1;
	}
	//预处理从第 i 头 H 牛和第 j 头 G 牛开始往后的最大连续匹配数 
}
int solve(){
	init();
	memset(f,-0x3f,sizeof(f));
	f[0][0][0]=f[0][0][1]=0;
	for(int i=0;i<=cnt1;i++)
	{
		for(int j=0;j<=cnt2;j++)
		{
			int s;
			s=max(nb[i]-j-1,0);
			if(i+s<=cnt1&&g[i+1][j+1]>=s)f[i+s][j+s][1]=max(f[i+s][j+s][1],f[i][j][0]);
			s=max(na[j]-i-1,0);
			if(j+s<=cnt2&&g[i+1][j+1]>=s)f[i+s][j+s][0]=max(f[i+s][j+s][0],f[i][j][1]);
			//转换种类的转移 
			if(i<=cnt1-1)f[i+1][j][0]=max(f[i+1][j][0],f[i][j][0]+a[i+1].v);
			if(j<=cnt2-1)f[i][j+1][1]=max(f[i][j+1][1],f[i][j][1]+b[j+1].v);
			if(i<=cnt1-1&&j<=cnt2-1&&check(i+1,j+1))
			{
				f[i+1][j+1][0]=max(f[i+1][j+1][0],f[i][j][0]);
				f[i+1][j+1][1]=max(f[i+1][j+1][1],f[i][j][1]);
			}
			//不转换种类的转移 
		}
	}
	return max(f[cnt1][cnt2][0],f[cnt1][cnt2][1]);
}
int main(){
	scanf("%d%d%d",&t,&n,&k);
	for(int i=1;i<=n;i++)
	{
		char c;
		int x,v;
		cin>>c;
		scanf("%d%d",&x,&v);
		if(c=='H')
		{
			cnt1+=1;
			a[cnt1]=(cow){x,v};
		}
		else
		{
			cnt2+=1;
			b[cnt2]=(cow){x,v};
		}
		//将奶牛分类放入数组中 
	}
	if(t==1)
	{
		for(int i=1;i<=cnt1;i++)
			a[i].v=-a[i].v;
		for(int i=1;i<=cnt2;i++)
			b[i].v=-b[i].v;
		//将 T=1 的情况转化为 T=2 的情况 
		printf("%d",-solve());
	}
	else printf("%d",solve());
	return 0;
}
