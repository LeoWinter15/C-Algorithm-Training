// Source: https://www.luogu.com.cn/article/i0oqvl99
#include<bits/stdc++.h>
using namespace std;
int m,q,res[100005];
char S[2000005];
int getint(int s,int &x){
	x=0;
	while(isdigit(S[s])){
		x=x*10+(S[s]^'0');
		s++;
	}
	return s;
}
int calc(int s,int l,int r){
	if(isdigit(S[s])){
		int tmp;
		int ret=getint(s,tmp);
		for(int i=l;i<=r;i++)
			res[i]=tmp;
		return ret;
	}
	int sep;
	int stt=getint(s+2,sep);
	if(S[s+1]=='>'){
		int neg=calc(stt+1,sep+1,r);
		return calc(neg+1,l,sep);
	}
	else{
		int neg=calc(stt+1,l,sep-1);
		return calc(neg+1,sep,r);
	}
}
int main(){
	scanf("%d%d%s",&m,&q,S);
	calc(0,1,m+1);
	for(;q;q--){
		int x;
		scanf("%d",&x);
		printf("%d\n",res[min(x,m+1)]);
	}
	return 0;
}
