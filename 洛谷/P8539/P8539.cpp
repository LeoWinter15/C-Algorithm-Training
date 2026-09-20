#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN =1e7+3;
int n,m,v,w,l,F[MAXN],G[MAXN],A[MAXN],X[MAXN],K[MAXN];
i64 ans1,ans2; char _file[256];
int qread(){
	int w=1,c,ret;
	while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
	while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
	return ret*w;
}
int main(int argc,char **argv){
	n=qread(),m=qread(),v=qread();
	up(1,n,i) A[i]=qread();
	up(1,m,i) X[i]=qread(),K[i]=qread();	
    A[0]=-INF;
	up(1,n,i){
		A[i]=w=A[i]-i*v;
		if(w>=A[F[i-1]]) G[i]=F[i-1],F[i]=i; else
		if(w>=A[G[i-1]]) G[i]=i,F[i]=F[i-1]; else
		G[i]=G[i-1],F[i]=F[i-1];
	}
	up(1,m,i){
		int x=X[i],k=K[i],y=x+k-1; l=0;
		if(y<n) l=max(0,x*v+(F[y]==x?A[G[y]]+(G[y]>x):A[F[y]]+(F[y]>x)));
        ans1^=l,ans2+=l;
	}
    printf("%lld %lld\n",ans1,ans2);
	return 0;
}

