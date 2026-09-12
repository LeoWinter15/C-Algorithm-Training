#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a,q,d[N],ans[N],l,r,tot;
struct kk{
	int val,id;
	bool operator<(const kk &x)const{
		return val<x.val;
	}
}c[N];
struct seg_tree{
	#define ls p<<1
	#define rs p<<1|1
	int ma[N<<2];
	void push_up(int p){
		ma[p]=max(ma[ls],ma[rs]);
		return;
	}
	void build(int p,int l,int r){
		if(l==r){
			ma[p]=d[l];
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		push_up(p);
		return;
	}
	void change(int p,int l,int r,int x,int c){
		if(l==r){
			ma[p]=c;
			return;
		}
		int mid=l+r>>1;
		if(x<=mid)change(ls,l,mid,x,c);
		if(mid<x)change(rs,mid+1,r,x,c);
		push_up(p);
		return;
	}
	int query(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return ma[p];
		int mid=l+r>>1,res=0;
		if(L<=mid)res=max(res,query(ls,l,mid,L,R));
		if(mid<R)res=max(res,query(rs,mid+1,r,L,R));
		return res;
	}
	#undef ls
	#undef rs
}seg;
void add(kk x){
	for(int i=tot;i>=1;i--){
		if(c[i].id==x.id){
			c[i].val=x.val;
			for(int j=i-1;j>=1;j--){
				if(c[j]<c[j+1])swap(c[j],c[j+1]);
			}
			return;
		}
	}
	c[tot+1]=x;
	for(int i=tot;i>=1;i--){
		if(c[i]<c[i+1])swap(c[i],c[i+1]);
	}
	return;
}
signed main(){
	scanf("%lld%lld",&n,&a);
	tot=min(n,10ll);
	for(int i=1;i<=n;i++){
		scanf("%lld",&d[i]);
		add({d[i],i});
	}
	seg.build(1,1,n);
	scanf("%lld",&q);
	while(q--){
		char op[3];
		scanf("%s",op);
		if(op[0]=='E'){
			int i,e;
			scanf("%lld%lld",&i,&e);
			seg.change(1,1,n,i,c[e].val+1);
			for(int j=e-1;j>=1;j--){
				c[j].val++;
				seg.change(1,1,n,c[j].id,c[j].val);
			}
			add({c[e].val+1,i});
		}
		if(op[0]=='F'){
			int b,now;
			scanf("%lld",&b);
			if(b==a){
				printf("0\n");
				continue;
			}
			if(b<a){
				int l=1,r=n-a,res=n-a+1;
				now=seg.query(1,1,n,b,a-1);
				while(l<=r){
					int mid=l+r>>1;
					if(seg.query(1,1,n,a+1,a+mid)>now){
						r=mid-1;
						res=mid;
					}
					else l=mid+1;
				}
				res--;
				printf("%lld\n",a-b+res);
				continue;
			}
			now=seg.query(1,1,n,a+1,b);
			int l=1,r=a-1,res=a;
			while(l<=r){
				int mid=l+r>>1;
				if(seg.query(1,1,n,a-mid,a-1)>now){
					r=mid-1;
					res=mid;
				}
				else l=mid+1;
			}
			res--;
			printf("%lld\n",b-a+res);
		}
	}
	return 0;
}

