#include<bits/stdc++.h>
using namespace std;
int s,h,v,n;
double ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>s>>h>>v>>n;
	ans=1.0*v/s;//原始水面高度 
	for(;n--;){
		double lc,md;
		cin>>lc>>md;
		if(md>=1)ans+=lc*lc*lc/s;//完全浸入水中 
		else ans+=lc*lc*lc*md/s;//不完全浸入水中 
		if(ans>=h){//有溢出的水 
			cout<<h;//因为已经有溢出的水，所以无论如何都是满的，直接输出水池的高 
			return 0;
		}
	}
	printf("%.7lf",ans);
	return 0;
}

