// Source: https://www.luogu.com.cn/article/tlapphcr
#include<bits/stdc++.h>
using namespace std;
const int MAXD=1e6+10;
const int MAXN=30+5;
int dp[MAXD];
int n,v;

struct node{
	int a,b;
}t[MAXN];

bool cmp(node s1,node s2){
	return s1.a+s1.b>s2.a+s2.b;
}

int main(){
	memset(dp,0x3f,sizeof(dp));
	scanf("%d%d",&n,&v);
	int sum=0;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&t[i].a,&t[i].b);
		if(t[i].a+t[i].b>0)
			sum+=t[i].a+t[i].b;
	}
	sort(t+1,t+n+1,cmp);
	if(sum<v){
		printf("-1");
		return 0;
	}
	dp[0]=0;
	for(int i=1;i<=n;++i){
		if(t[i].a+t[i].b>=0){
			for(int j=sum;j>=t[i].a+t[i].b;--j){
				int now=dp[j-t[i].a-t[i].b]+t[i].a-t[i].b;
				if(abs(now)<abs(dp[j]))
					dp[j]=now;
			}
		}else{
			for(int j=0;j<=sum+t[i].a+t[i].b;++j){
				int now=dp[j-t[i].a-t[i].b]+t[i].a-t[i].b;
				if(abs(now)<abs(dp[j]))
					dp[j]=now;
			}
		}
	}
	int ans=INT_MAX;
	for(int i=v;i<=sum;++i)
		ans=min(ans,abs(dp[i]));
	printf("%d",ans);
	return 0;
}
