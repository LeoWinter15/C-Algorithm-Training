#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while (T--) {
		int x;
		cin>>x;
		if(!(x&(x-1))){
			if(x==2){
				cout<<3<<'\n';
			}else cout<<x<<'\n';
		} else {
			if (x==3){
				cout<<2<<'\n';
			}else{
                x|=(x>>1);
                x|=(x>>2);
                x|=(x>>4);
                x|=(x>>8);
                x|=(x>>16);
                x|=(x>>32);
                cout<<x<<'\n';
            }
		}
	}
	return 0;
}
