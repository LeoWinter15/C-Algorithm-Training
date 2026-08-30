#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	int n, k, rs, u, v, c[N];
	vector<int> G[N]; set<int> s[N];
	void dfs(int u, int fa) {
		s[u].insert(c[u]);
		for (int v : G[u]) {
			if (v == fa) continue;
			dfs(v, u);
			if (s[u].size() < s[v].size()) s[u].swap(s[v]);
			for (int x : s[v]) s[u].insert(x);
		}
		if (s[u].size() >= k) s[u].clear(), rs ++;
	}
	int main() {
		cin >> n >> k;
		REP(i, 1, n) cin >> c[i];
		REP(i, 2, n) cin >> u >> v, G[u].pb(v), G[v].pb(u);
		dfs(1, 0);
		cout << rs << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
