// Source: https://www.luogu.com.cn/article/lxbi7xzg
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#define MAXN 110
using namespace std;
int n,m,lnorth,rnorth,lsouth,rsouth;
double k1,k2,ans=(1LL<<62);//记得开最大最
inline double square(int x){return 1.00*x*x;}
inline double min(double x,double y){return x<y?x:y;}
inline double Area(int num,int len,double k){//求出面积
	if(!num)return 0;//记得特判，防止除0！
	double s=square(len/num)*k*(num-len%num)+square(len/num+1)*k*(len%num);
	return s;
}
void work(){
	if(n%m==0){//第一种情况，直接特判掉就好
		ans=Area(lnorth,100,k1)+Area(lnorth*lsouth,100,k2);
		printf("%.1lf\n",ans);
		return;
	}
	for(int i=lnorth*lsouth;i<=100-rnorth*rsouth;i++){
		double area=Area(lnorth,i,k1)+Area(rnorth,100-i,k1)+Area(lnorth*lsouth,i,k2)+Area(rnorth*rsouth,100-i,k2);
		if(ans>area)ans=area;//更新答案
		else break;//运用单调性
	}
	printf("%.1lf\n",ans);
}
void init(){
	scanf("%lf%lf%d%d",&k1,&k2,&m,&n);
	lnorth=m-n%m;rnorth=n%m;
	lsouth=n/m;rsouth=n/m+1;//求出前段与后段的南北墙的草地块数
}
int main(){//主函数So easy!
	init();
	work();
	return 0;
}
