#include<bits/stdc++.h>
#define LL long long
#define CPPname using namespace std
CPPname;
LL n;
const int MAX=1000010;
LL a[MAX];
int main(){
	cin>>n;
	LL ans=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	const int c=n/2;
	for(int i=1;i<=n/2;i++){
		if(a[i]==a[i+c])ans+=2;
		//cout<<i<<" "<<i+n/2<<" ";
	}
	
	cout<<ans;
	return 0;
}


