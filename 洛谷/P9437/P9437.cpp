#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;
const int mod = 998244353;

struct node {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int s[MAXN];

ll a[MAXN], b[MAXN], f[MAXN], g[MAXN], t[MAXN];

// f: up, g: down

void dfs1(int u, int p) {
	f[u] = s[u] = 1;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v; if (v == p) continue;
		dfs1(v, u), s[u] += s[v];
		f[u] = (f[u] + b[v] * f[v] % mod) % mod;
	}
	t[u] = f[u];
}

int n; ll ans;

void dfs2(int u, int p) {
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v; if (v == p) continue;
		g[u] = (g[u] + s[v] * (f[u] - b[v] * f[v] % mod + mod) % mod) % mod;
		f[v] = (f[v] + b[u] * (f[u] - b[v] * f[v] % mod + mod) % mod) % mod, dfs2(v, u);
	}
	g[u] = (g[u] + (n - s[u]) * t[u] % mod) % mod;
}

int main() {
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
		scanf("%lld", &a[i]), b[i] = 1;
		if (!a[i]) b[i] = 10;
		else for (x = a[i]; x; x /= 10, b[i] = b[i] * 10 % mod);
	}
	for (int i = 2, u; i <= n; i++) scanf("%d", &u), add(u, i), add(i, u);
	dfs1(1, 0), dfs2(1, 0);
	for (int i = 1; i <= n; i++) ans = (ans + a[i] * (f[i] + g[i]) % mod) % mod;
	printf("%lld", ans);
}
