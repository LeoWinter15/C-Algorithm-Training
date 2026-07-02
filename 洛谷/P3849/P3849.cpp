#include <bits/stdc++.h>
using namespace std;
const int Maxn=10001,MaxU=10001;
double a,b,c,d,e,f,data[MaxU],cha[Maxn][4],tmp[3];;
int n,M,N,U;
int main(){
	scanf("%d%d%d%d",&n,&N,&M,&U);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
		tmp[0]=a/d;
		tmp[1]=b/e;
		tmp[2]=c/f;
		cha[i][1]=log(max(tmp[1],max(tmp[0],tmp[2])));
		cha[i][2]=log(max(tmp[1]+tmp[0],max(tmp[1]+tmp[2],tmp[0]+tmp[2])));
		cha[i][3]=log(tmp[1]+tmp[0]+tmp[2]);
	}
	for(int i=1;i<=n;i++)
		for(int j=U;j>=1;j--)
			for(int k=1;k<=3;k++)
				if(j/k>=1)
					data[j]=max(data[j],data[j/k]+cha[i][k]);
	printf("%.3lf",log(M)-log(N)+data[U]);
	return 0;
}
