// Source: https://www.luogu.com.cn/article/zlydojmk
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
const int MAXN = 200010;
const ll INF = 1e17+1;

int n, m;;

struct edge{
	int ne, to;
}e[MAXN<<1];
int fir[MAXN], num = 0;
inline void join(int a, int b)
{
	e[++num].ne = fir[a];
	fir[a] = num;
	e[num].to = b;
}

struct mat{
	ll ele[2][2];
	mat(int type = 0)
	{
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				ele[i][j] = INF;
		if(type == 1) {
			for(int i=0;i<2;i++)
				ele[i][i] = 0;
		}
	}
	ll& operator()(const int ix, const int iy){return ele[ix][iy];}
    // 重定义的矩阵乘法
	inline friend mat operator*(mat mx, mat my)
	{
		mat res(0);
		for(int i=0;i<2;i++)
			for(int k=0;k<2;k++)
				for(int j=0;j<2;j++)
					res(i,j)=min(res(i,j), mx(i,k)+my(k,j));
		return res;
	}
};

ll val[MAXN], f[MAXN];
mat g[MAXN];

int dep[MAXN], pa[MAXN], siz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], rev[MAXN], end[MAXN], cnt = 0;

void dfs1(int u, int fa)
{
	siz[u] = 1; dep[u] = dep[fa] + 1; pa[u] = fa;
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]) son[u] = v;
	}
}
void dfs2(int u, int t)
{
	dfn[u] = ++cnt; rev[cnt] = u; top[u] = t; end[t] = max(end[t], cnt);
	g[u](0, 0) = 0;   g[u](0, 1) = val[u];
	g[u](1, 0) = INF; g[u](1, 1) = 0;
	f[u] = 0;
	if(son[u]) {
		
		dfs2(son[u], t);
		f[u] += f[son[u]];
	}
	else g[u](0, 0) = INF; //为了保证叶结点转移的合法
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == pa[u] || v == son[u]) continue;
		dfs2(v, v);
		g[u](0, 0) += f[v]; //g 数组的转移不包括重儿子
		f[u] += f[v];
	}
	if(!son[u]) f[u] = val[u]; // 特判叶结点
	else f[u] = min(f[u], val[u]); // 记得两者取最小
}
struct {
	int l, r;
	mat val;
}t[MAXN<<2];
inline void pushUp(int k)
{
	t[k].val = t[k<<1].val*t[k<<1|1].val;
}
void build(int l, int r, int k)
{
	t[k].l = l; t[k].r = r;
	if(l == r) {
		t[k].val = g[rev[l]];
		return ;
	}
	int mid = t[k].l+t[k].r>>1;
	build(l, mid, k<<1);
	build(mid+1, r, k<<1|1);
	pushUp(k);
}
void update(int x, int k)
{
	if(t[k].l == t[k].r) {
		t[k].val = g[rev[x]]; //由于有在树外记录转移矩阵，直接赋值即可
		return ;
	}
	int mid = t[k].l+t[k].r>>1;
	if(x <= mid) update(x, k<<1);
	else update(x, k<<1|1);
	pushUp(k);
}
mat query(int x, int y, int k)
{
	if(t[k].l == x && t[k].r == y) return t[k].val;
	int mid = t[k].l+t[k].r>>1;
	if(y <= mid) return query(x, y, k<<1);
	else if(x >= mid+1) return query(x, y, k<<1|1);
	else return query(x, mid, k<<1)*query(mid+1, y, k<<1|1);
}
inline void updatePath(int x, ll z)
{
	val[x] += z;
	g[x](0, 1) = val[x];
	mat bef, aft;
	while(x)
	{
		bef = query(dfn[top[x]], end[top[x]], 1);
        // 记录更新之前的矩阵
		update(dfn[x], 1);
		aft = query(dfn[top[x]], end[top[x]], 1);
		x = pa[top[x]];
		g[x](0, 0) += min(aft(0, 0), aft(0, 1)) - min(bef(0, 0), bef(0, 1)); 
        // 更新转移矩阵，为下一条链的修改做准备，注意这里需要先减去原先的值
	}
}
inline ll querySubtree(int x)
{
	mat res = query(dfn[x], end[x], 1); // 查询时只需要从当前点到链尾即可
	return min(res(0, 0), res(0, 1));
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&val[i]);
	for(int i=1;i<n;i++)
	{
		int a, b;
		scanf("%d%d",&a,&b);
		join(a, b);
		join(b, a);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for(int i=1;i<=n;i++)
		end[i] = end[top[i]];
	build(1, n, 1);
	scanf("%d",&m);
	while(m--)
	{
		char opt; int x; ll z;
		cin>>opt;
		if(opt == 'C') {
			scanf("%d%lld",&x,&z);
			updatePath(x, z);
		}
		else {
			scanf("%d",&x);
			printf("%lld\n",querySubtree(x));
		}
	}
	return 0;
}
