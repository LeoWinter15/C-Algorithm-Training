// Source: https://www.luogu.com.cn/article/7nscu2oa
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
	
	ll t;
	
	cin>>t;
	while(t--){
		
		ll n,m;
		cin>>n>>m;
		fflush(stdin);
		
		ll x1_x2_y1_y2,x1_x2__y1__y2,x2__x1__y1__y2,y2__y1_x1_x2;
		
		cout<<"SCAN 1 1"<<endl;
		
		//求出 x1 + x2 + y1 + y2
		cin>>x1_x2_y1_y2;
		fflush(stdin);
		x1_x2_y1_y2+=4;
		
		cout<<"SCAN 1 "<<m<<endl;
		
		//求出 x1 + x2 - y1 - y2
		cin>>x1_x2__y1__y2;
		fflush(stdin);
		x1_x2__y1__y2+=2-2*m;
		
		//解出 x1 + x2 和 y1 + y2
		ll x1_x2=(x1_x2__y1__y2+x1_x2_y1_y2)/2;
		ll y1_y2=(x1_x2_y1_y2-x1_x2__y1__y2)/2;
		
		ll mid_x1_x2=x1_x2/2;
		
		cout<<"SCAN "<<mid_x1_x2<<" "<<m<<endl;
		
		cin>>x2__x1__y1__y2;
		fflush(stdin);
		x2__x1__y1__y2-=2*m;
		
		//求出 x2 - x1
		ll x2__x1=x2__x1__y1__y2+y1_y2;
		
		//解出 x1 和 x2
		ll x2=(x2__x1+x1_x2)/2,x1=x1_x2-x2;
		
		ll mid_y1_y2=y1_y2/2;
		
		cout<<"SCAN 1 "<<mid_y1_y2<<endl;
		
		cin>>y2__y1_x1_x2;
		fflush(stdin);
		y2__y1_x1_x2+=2;
		
		//求出 y2 - y1
		ll y2__y1=y2__y1_x1_x2-x1_x2;
		
		//解出 y1 和 y2
		ll y2=(y2__y1+y1_y2)/2,y1=y1_y2-y2;
		
		ll op1,op2;
		
		cout<<"DIG "<<x1<<" "<<y1<<endl;
		cin>>op1;
		fflush(stdin);
		
		if(op1){
			
			cout<<"DIG "<<x2<<" "<<y2<<endl;
			cin>>op2;
			fflush(stdin);
		}
		else{
			
			cout<<"DIG "<<x1<<" "<<y2<<endl;
			cin>>op1;
			fflush(stdin);
			
			cout<<"DIG "<<x2<<" "<<y1<<endl;
			cin>>op2;
			fflush(stdin);
		}
	}
	
	return 0;
}
