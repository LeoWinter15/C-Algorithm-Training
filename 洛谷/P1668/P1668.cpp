// Source: https://www.luogu.com.cn/article/xky5w50b
#include <bits/stdc++.h>
using namespace std;

struct segment{
	int l,r;
	bool operator<(const segment &x) const{
		return l<x.l;
	} // 重载小于号，用于 sort()。也可以用 cmp() 函数实现同样功能。
}range[25005];

int main(){
	int n,ed;
	scanf("%d%d",&n,&ed);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&range[i].l,&range[i].r);
	sort(range+1,range+n+1);
	int st=1,ans=0;
	for(int i=1,j=1;i<=n;){
		int r=0;
		while(j<=n&&range[j].l<=st){ // 左端点要 <= st，即该区间能覆盖 st 
			r=max(r,range[j].r); // 找右端点最大的
			j++;
		}
		if(r<st) break; // 找不到能覆盖 st 的区间
		ans++;
		if(r>=ed){ // 有解，输出
			printf("%d\n",ans);
			return 0;
		}
		st=r+1;i=j;
	}
	printf("-1\n");
	return 0;
}
