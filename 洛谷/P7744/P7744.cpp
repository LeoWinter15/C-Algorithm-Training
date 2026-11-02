// Source: https://www.luogu.com.cn/article/rb88lkg1
#include<bits/stdc++.h>
using namespace std;
int n,m,u=1,f=2,r=3,op=1;
long long ans;
void solve(int tp,int len){
	ans+=(len/4)*14;	//批量解决大部分滚动
	len%=4;
	for(int i=1,tmp;i<=len;i++){	//模拟剩下的滚动
		if(tp==1){	//如果是向左滚
			tmp=7-r;
			r=u;
			u=tmp;
		}
		else{	//否则一定是向右滚
			tmp=7-u;
			u=r;
			r=tmp;
		}
		ans+=u;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,tmp;i<=n;i++){
		ans+=u;
		solve(op,m-1);	//注意到上一行已经走了一步了，所以这里是 m-1
		tmp=7-f;f=u;u=tmp;	//模拟骰子向下滚动
		op*=-1;	//换方向
	}
	printf("%lld",ans);	 
	return 0;
}
