#include<bits/stdc++.h>
using namespace std;

#define N 505
#define M 505
#define pii pair<int,int>

int n,a[N];
int cnt1=0,cnt2=0;	// cnt1：a_i=1 的石子堆个数，cnt2：a_i>1 的石子堆个数
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	auto get=[](){	// 得到一个 i 满足 a_i=1
		for(int i=1;i<=n;++i)
			if(a[i]==1){
				cout<<i<<endl;
				a[i]=0,--cnt1;
				int tp; cin>>tp;
				return i;
			}
		return -1;
	};
	
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(a[i]==1) ++cnt1;
		else if(a[i]>1) ++cnt2;
	}
	
	for(int p;;){
		cin>>p;
		if(a[p]==1){
			// 取石子
			cout<<1<<endl;
			a[p]=0,--cnt1;
			
			// 指定堆
			if(cnt1==0) break;
			p=get();
		}else{
			if(cnt2==1){
				if(cnt1%2){
					cout<<a[p]-1<<endl;
					a[p]=1,++cnt1,--cnt2;
					break;
				}else{
					cout<<a[p]<<endl;
					a[p]=0,--cnt2;
					break;
				}
			}else{
				// 取石子
				cout<<a[p]-1<<endl;
				a[p]=0,--cnt2;
				
				// 指定堆
				cout<<p<<endl;
				cin>>p;
			}
		}
	}
	
	
	// n'=0,[F]=0,n mod 2=0 的必胜策略
	for(int p;;){
		// 指定
		if(cnt1<=0) break;
		p=get();
		
		// 取石子
		cin>>p;
		a[p]=0,--cnt1;
		cout<<1<<endl;
	}
	
	cout<<-1<<endl;
	return 0;
}

