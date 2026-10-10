// Source: https://www.luogu.com.cn/article/ceztxs5g
#include <bits/stdc++.h>
using namespace std;
const int N = 100005,U = 200005;
int n,d,m,h[N];
const int V = U*60;
struct Treap{
	struct Node{ int lc,rc,pos,val,siz; }t[V]; int _cnt;
	inline int New_node(int v){ ++_cnt,t[_cnt].val = v,t[_cnt].pos = rand(),t[_cnt].siz = 1; return _cnt; }
	inline int Copy_node(int p){ return memcpy(t+(++_cnt),t+p,20),_cnt; }
	inline void up(int o){ t[o].siz = t[t[o].lc].siz + t[t[o].rc].siz + 1; }
	inline int getrnk(int p,int v){
		static int ans; ans = 0;
		while (p) if (t[p].val > v) p = t[p].lc; else ans += 1 + t[t[p].lc].siz,p = t[p].rc;
		return ans;
	}
	inline void spilt(int p,int k,int &x,int &y){
		if (!p){ x = y = 0; return;	}
		if (t[t[p].lc].siz >= k) y = Copy_node(p),spilt(t[y].lc,k,x,t[y].lc),up(y);
		else x = Copy_node(p),spilt(t[x].rc,k-t[t[x].lc].siz-1,t[x].rc,y),up(x);
	}
	inline int merge(int x,int y){
		if (!x || !y) return x|y;
		if (t[x].pos < t[y].pos){ x = Copy_node(x),t[x].rc = merge(t[x].rc,y),up(x); return x;}
		y = Copy_node(y),t[y].lc = merge(x,t[y].lc),up(y); return y;
	}
	inline int add(int p,int v){
		static int k,x,y; k = getrnk(p,v); spilt(p,k,x,y);
		return merge(merge(x,New_node(v)),y);
	}
	inline int del(int p,int v){
		static int k,x,y,z; k = getrnk(p,v); spilt(p,k,x,y); spilt(x,k-1,x,z);
		return merge(x,y);
	}
 	int aa[505],llen;
	inline void Get(int rt){ if (t[rt].lc) Get(t[rt].lc); aa[++llen] = t[rt].val; if (t[rt].rc) Get(t[rt].rc); }
	inline void getall(int rt,int *a,int &len){
		if (!rt) len = 0; else llen = 0,Get(rt),len = llen,memcpy(a,aa,len+1<<2);
	}
}Tr;
vector<int>G[N],Gt[N];
inline int query(int x,int t){
	int L = 1,R = Gt[x].size()-1,Mid,Ans = 0;
	while (L <= R){
		Mid = L+R>>1;
		if (Gt[x][Mid] <= t) Ans = G[x][Mid],L = Mid + 1; else R = Mid - 1;
	}
	return Ans;
}
int ans,lena,lenb,a[505],b[505];
inline void upd(int x){ x < ans ? ans = x : 0; }
inline void QUery(){
	static int x,y,t,i,j;
	cin >> x >> y >> t,++x,++y,ans = 1000000000;
	Tr.getall(query(x,t),a,lena); Tr.getall(query(y,t),b,lenb);
	i = j = 1;
	while (i < lena && j < lenb) if (a[i] < b[j]) upd(b[j]-a[i]),++i; else upd(a[i]-b[j]),++j;
	if (i == lena){ while (j <= lenb) upd((a[i] > b[j]) ? (a[i] - b[j]) : (b[j] - a[i])),++j; }
	else if (j == lenb){ while (i <= lena) upd((a[i] > b[j]) ? (a[i] - b[j]) : (b[j] - a[i])),++i; }
	cout << ans << '\n'; fflush(stdout);
}
set<int>S[N];
int main(){
	int i,q,x,y,vx,vy,t;
	srand(time(NULL));
	cin >> n >> d >> m >> q;
	for (i = 1; i <= n; ++i) cin >> h[i];
	for (i = 1; i <= n; ++i) G[i].push_back(0),Gt[i].push_back(0);
	for (i = 1; i <= m; ++i){
		cin >> x >> y,++x,++y; if (x > y) swap(x,y); vx = h[x],vy = h[y];
		Gt[x].push_back(i),Gt[y].push_back(i);
		if (S[x].count(y)){//have -> none
			S[x].erase(y);
			G[x].push_back(Tr.del(G[x].back(),vy));
			G[y].push_back(Tr.del(G[y].back(),vx));
		}
		else{//none -> have
			S[x].insert(y);
			G[x].push_back(Tr.add(G[x].back(),vy));
			G[y].push_back(Tr.add(G[y].back(),vx));
		}
	}
	while (q--) QUery();
	return 0;
}
