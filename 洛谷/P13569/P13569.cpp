#include<bits/stdc++.h>
using namespace std;
int t;
double a,b,c,d,e,f,ppmax;
int main(){
	cin>>t;
	while(t--){
		cin>>ppmax>>a>>b>>c>>d>>e>>f;
		cout<<fixed<<setprecision(2)<<(300.0*a+300.0*b+200.0*c+100.0*d+50.0*e)/(300.0*(a+b+c+d+e+f))*100.0<<"% ";
		cout<<(int)(max(0.0,((320*a+300*b+200*c+100*d+50*e)*5*ppmax/(320*(a+b+c+d+e+f))-4*ppmax))+0.5)<<'\n';
	}
}
