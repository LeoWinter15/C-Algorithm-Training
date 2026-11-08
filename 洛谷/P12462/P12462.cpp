// Source: https://www.luogu.com.cn/article/7us57kei
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define Rep(i,a,b) for(int i = (a);i >= (b);--i)

#ifdef ONLINE_JUDGE
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#endif

int read(){
	int x = 0;
	char c = getchar();
	for(;!isdigit(c);c = getchar());
	for(;isdigit(c);c = getchar()) x = x * 10 + c - '0';
	return x;
}

using ll = long long;
using vec = basic_string<int>;

const int N = 3e5 + 5,M = 3e3 + 5,K = 105;

int n,q,C,P,bg[N],ed[N],bl[N],dfn[N],son[N],tot,st[20][N];
ll dep[N],mxd[N],D,ans;
vec ST[14][M];
vector<pair<int,ll>> G[N],H[N];
vector<pair<ll,int>> L;

bool cmp(int i,int j){ return dfn[i] < dfn[j]; }

void dfs0(int u,int ft){
	st[0][dfn[u] = ++tot] = ft;
	for(auto[v,w] : G[u]) if(v != ft) dep[v] = dep[u] + w,dfs0(v,u);
}

int lca(int x,int y){
	if(x == y) return x;
	if((x = dfn[x]) > (y = dfn[y])) swap(x,y);
	int i = __lg(y - x++);
	return min(st[i][x],st[i][y - (1 << i) + 1],cmp);
}
	
void dfs0(int u,int ft,ll d){
	if(d >= D) D = d,P = u;
	for(auto[v,w] : H[u]) if(v != ft) dfs0(v,u,d + w);
}

void dfs1(int u,int ft,ll d){
	mxd[u] = d,son[u] = 0;
	for(auto[v,w] : H[u]) if(v != ft){
		dfs1(v,u,d + w),mxd[u] = max(mxd[u],mxd[v]);
		if(mxd[v] >= mxd[son[u]]) son[u] = v;
	}
}

void dfs2(int u,int ft,ll D){
	if(H[u].size() == 1 && ft) L.emplace_back(-D,u);
	for(auto[v,w] : H[u]) if(v != ft) dfs2(v,u,(v == son[u] ? D : 0) + w);
	H[u].clear();
}

vec sol(vec x,int k = K){
	ranges::sort(x,cmp),x.erase(unique(begin(x),end(x)),end(x));
	Rep(i,(int)x.size() - 1,1) x += lca(x[i],x[i - 1]);
	ranges::sort(x,cmp),x.erase(unique(begin(x),end(x)),end(x));
	rep(i,1,(int)x.size() - 1){
		int y = lca(x[i - 1],x[i]); ll z = dep[x[i]] - dep[y];
		H[y].emplace_back(x[i],z),H[x[i]].emplace_back(y,z);
	}
	L.clear(),D = 0,dfs0(x[0],0,0),dfs1(P,0,0),dfs2(P,0,0);
	ranges::nth_element(L,begin(L) + k - 1),L.resize(min((int)L.size(),k - 1));
	ll sum = 0; vec y = {P};
	for(auto[d,u] : L) sum -= d,y += u;
	ans = max(ans,sum);
	return y;
}

int main(){
	n = read();
	rep(i,1,n - 1){
		int u = read(),v = read(),w = read();
		G[u].emplace_back(v,w),G[v].emplace_back(u,w);
	}
	dfs0(1,0);
	rep(j,1,19) rep(i,1,n - (1 << j) + 1)
		st[j][i] = min(st[j - 1][i],st[j - 1][i + (1 << (j - 1))],cmp);
	C = (n - 1) / K + 1;
	rep(i,1,C){
		bg[i] = ed[i - 1] + 1,ed[i] = i == C ? n : bg[i] + K - 1;
		rep(j,bg[i],ed[i]) bl[j] = i,ST[0][i] += j;
	}
	rep(j,1,13) rep(i,1,C - (1 << j) + 1)
		ST[j][i] = sol(ST[j - 1][i] + ST[j - 1][i + (1 << (j - 1))]);
	for(q = read();q--;){
		int l = read(),r = read(),k = read(),L,R,i; vec P;
		if(bl[l] == bl[r]) rep(i,l,r) P += i;
		else {
			rep(i,l,ed[bl[l]]) P += i;
			rep(i,bg[bl[r]],r) P += i;
			if((L = bl[l] + 1) <= (R = bl[r] - 1))
				i = __lg(R - L + 1),P += ST[i][L] + ST[i][R - (1 << i) + 1];
		}
		ans = 0,sol(P,k),printf("%lld\n",ans);
	}
	return 0;
}
