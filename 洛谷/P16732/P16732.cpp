#include<bits/stdc++.h>
#define N 100002
using namespace std;
map<int,bool> st;
int a[N],n,q,T,all,pos,val;
inline bool check(int x){ // 返回 x 是否异或奇 
	return (__builtin_popcount(x)&1);
}
inline void solve(){
	st.clear();
	all=0;
	cin>>n>>q;
	for(int i=1; i<=n; i++){
		cin>>a[i]; all^=a[i];
		if(check(a[i])) st.insert({i,1});
	}
	while(q--){
		cin>>pos>>val;
		++pos;
		all^=a[pos];
		all^=val;
		if(check(a[pos])) st.erase(st.find(pos)); 
		a[pos]=val;
		if(check(val)) st.insert({pos,1}); 
		if(!check(all)) cout<<n<<" ";
		else cout<<max(n-st.begin()->first,st.rbegin()->first-1)<<" ";
	}
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	for(int i=1; i<=T; i++) cout<<"Case #"<<i<<": ", solve();
	return 0;
}
