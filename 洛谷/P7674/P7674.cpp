// Source: https://www.luogu.com.cn/article/8vd4c1f5
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
char st[1000005];
int l1,l2,top,w[1000005];
int main(){
	ios::sync_with_stdio(false);
	cin>>s1>>s2;
	l1=s1.size();
	l2=s2.size();
	s2=" "+s2;
	bool ok=0;
	for(int i=0;i<l1;i++){
		if(s1[i]!=s2[w[top]+1]&&s1[i]!=s2[1]){
			for(int j=1;j<=top;j++){
				cout<<st[j];
			}
			top=0;
			cout<<s1[i];
			ok=1;
//			cout<<top<<" "<<s1[i]<<" "<<111111<<endl;
			continue;
		}
		st[++top]=s1[i];
		if(s1[i]!=s2[w[top-1]+1]){
			w[top]=1;
		}
		else{
			w[top]=w[top-1]+1;
		}
		if(w[top]==l2){
			top-=l2;
		}
//		cout<<top<<" "<<s1[i]<<endl;
	}
	for(int i=1;i<=top;i++){
		cout<<st[i];
		ok=1;
	}
	if(!ok) cout<<"FRULA";
    return 0;
}
