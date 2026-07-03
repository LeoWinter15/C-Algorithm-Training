#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int sum,maxn,b[N];
int c[N],cnt[N],ans[N];
struct node
{
	int l,r,id;
	friend bool operator<(node a,node b)
	{
		if(a.l/maxn!=b.l/maxn)return a.l<b.l;
		else return (a.l/maxn)&1?a.r<b.r:a.r>b.r;
	}
}a[N];
inline void add(int x){sum+=cnt[x]==1,sum-=cnt[x]==2,cnt[x]++;}
inline void del(int x){sum-=cnt[x]==2,sum+=cnt[x]==3,cnt[x]--;}
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	maxn=sqrt(n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]),b[i]=c[i];
	sort(b+1,b+1+n);
	int pos=unique(b+1,b+1+n)-b-1;
    // cout<<unique(b+1,b+1+n)<<endl;
    // printf("%d\n",pos);
    // cout<<b<<endl;
    // cout<<b[1]<<b[2]<<b[3]<<b[4]<<b[5]<<b[6]<<endl;
	for(int i=1;i<=n;i++)c[i]=lower_bound(b+1,b+1+pos,c[i])-b;
	for(int i=1;i<=q;i++)scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i;
	sort(a+1,a+1+q);
	int l=1,r=0;
	for(int i=1;i<=q;i++)
	{
		while(l>a[i].l)add(c[--l]);
		while(r<a[i].r)add(c[++r]);
		while(l<a[i].l)del(c[l++]);
		while(r>a[i].r)del(c[r--]);
		ans[a[i].id]=sum;
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}
