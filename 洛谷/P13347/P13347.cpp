// Source: https://www.luogu.com.cn/article/en8n6s5v
#include <bits/stdc++.h>
using namespace std;
//double Round(const double& x) { return round(x * 1000) / 1000; }
int v, t, n, s, e;
int main() {
    cin >> n >> s >> e >> v;
    double ans = 1e18;
    if (v) ans = (double) (e - s) / v;
    for (int i = 1; i <= n; i++) {
    	cin >> t >> v;
    	if (v) ans = min(ans, (double) e / v + t);
	}
	printf("%.4f", ans);
    return 0;
}
