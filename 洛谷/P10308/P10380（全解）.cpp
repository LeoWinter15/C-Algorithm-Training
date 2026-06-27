#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e6+10; 

int n,m,p,ans1,ans2;
int fact[N];

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f),c=getchar();
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

void solution(){
	/*
		将 n-i 个元素分到 m-1 组中
		每组可以为空
		有 n-i+m-1 个元素，插 m-2 个板
		有 n-i+m-2 个空隙
		ans=C_{n-i+m-2}^{m-2}
		
		对于第 j 组，每组答案为：
		i*C_{n-i+m-2}^{m-2} (i ∈ [1,n])  *   j!
		
		对于前面的式子，用 O(n) 求出
		后面的预处理得到 
		
		最后的答案为：
		cgm(i*C_{n-i+m-2}^{m-2}) * cgm(j!)    (i∈[1,n] j∈[1,m])  
	*/
}

int ksm(int x,int y){
	int sum=1;
	while(y){
		if(y&1) sum=sum*x%p;
		x=x*x%p;
		y>>=1;
	}
	return sum;
}

int C(int x,int y){
	if(x<y) return 0;
	return fact[x]*ksm(fact[x-y],p-2)%p*ksm(fact[y],p-2)%p;
}

int lucas(int x,int y){
	if(y==0) return 1;
	return C(x%p,y%p)*lucas(x/p,y/p)%p;
}

void init(){
	fact[0]=1;
	for(int i=1;i<=n+m+2;i++) fact[i]=fact[i-1]*i%p;
}

signed main(){
	n=read(),m=read(),p=read();
	if(m==1){cout<<n%p;return 0;}
	init();
	for(int i=1;i<=n;i++) ans1=(ans1+i*lucas(n-i+m-2,m-2)%p)%p;
	for(int i=1;i<=m;i++) ans2=(ans2+fact[i])%p;
	cout<<ans1*ans2%p;
	return 0;
}

