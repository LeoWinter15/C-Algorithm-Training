#include <bits/stdc++.h>
using namespace std;
bool vis[1000005];
int vis1[1000005],a[1000005],n,c,s=0,ans[1000005];
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>c>>n;
	for (int i=1; i<=n; i++) {
		cin>>a[i];
		vis1[a[i]]++; //统计每个数出现多少次 
	}
	for (int i=1; i<=1000000; i++) {
		if (vis1[i])
			s++; //统计一共有几个数 
	}
	int s1=0;
	cout<<s<<'\n'; //先输出数的个数 
	for (int i=n; i>=1; i--) { //注意，是按照最后一次的出现顺序 
		if(!vis[a[i]]) { //如果这个数还没有被访问到 
			ans[++s1]=a[i]; //用ans数组记录下来 
			vis[a[i]]=1; //这个数标记为已访问 
		} else
			continue; //如果已经访问过了，就跳过 
	}
	for (int i=s; i>=1; i--) { //必须要倒过来输出 
		cout<<ans[i]<<' '; 
	}
	return 0;
}

