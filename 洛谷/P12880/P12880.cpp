// Source: https://www.luogu.com.cn/article/a0yo8inl
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1919810,M=0721;
ll n,a[N],ans;
vector<ll> v[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		v[a[i]].push_back(i); //输入的时候顺便把v给处理了 
	} 
	for(ll t=1;t<=1000000;t++){ //循环枚举 
		if(v[t+1].empty()||v[t].empty()) continue; //这个数字不存在或是与这个数字差为1的不存在 
		for(ll i=v[t].size()-1;i>=0;i--){
			if(!v[t+1].size()) break; //删完了防止越界 
			ll p=v[t+1].size()-1; //差为一的数字 
			if(v[t+1][p]>v[t][i]){
				ans++; //答案++ 
				v[t][i]=0; //这里不能直接删，因为可能删错数字 
				v[t+1].pop_back(); //这个可以删 
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
