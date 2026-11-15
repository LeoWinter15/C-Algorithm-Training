// Source: https://www.luogu.com.cn/article/vnwuqeaw
#include<bits/stdc++.h>
#define LoveFurina ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define F(x, l, r) for(int x = l; x <= r; ++x)
#define B(x, r, l) for(int x = r; x >= l; --x)
#define int long long
using namespace std;

const int INF = 4e18;

int n, tmp = 0;
int Min = -INF, Max = INF;

signed main() {
	LoveFurina;
	
	cin >> n;
	F (i, 1, n) {
		int m; cin >> m;
		int cur = m - 2 * tmp; tmp = m - tmp;
		if (i & 1) Max = min(Max, cur);
        else Min = max(Min, -cur);
	}
	cout << max(Max - Min + 1, 0LL);
	
return 0;
}

// 生命如同戏剧，你永远预料不到转折出现在哪一篇章。
// 世间的奇遇之所以存在，就是为了给世人带来转机。
