// Source: https://www.luogu.com.cn/article/jz7byxab
#include<bits/stdc++.h>
#define ll long long
#define p 998244353ll
#define N 500009
using namespace std;
int n,a[N];
ll f[N];
int sta[N],top,l[N],r[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i*=10)f[i]++;
	for(int i=1;i<=n;i++)f[i]+=f[i-1];
	for(int i=1;i<=n;i++)f[i]+=f[i-1];
	for(int i=1;i<=n;i++)f[i]+=f[i-1];
	for(int i=1;i<=n;i++)r[i]=n;
	for(int i=1;i<=n;i++){
		while(top&&a[sta[top]]<a[i]){
			r[sta[top]]=i-1;--top;
		}
		l[i]=sta[top]+1;
		sta[++top]=i;
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans+=(f[r[i]-l[i]+1]-f[i-l[i]]-f[r[i]-i])%p*a[i]%p;
	}
	cout<<ans%p<<"\n";return 0;
}
