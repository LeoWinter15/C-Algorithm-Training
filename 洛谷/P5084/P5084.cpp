// Source: https://www.luogu.com.cn/article/hodgh16f
#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e7 + 29;
int n, m, x, y, z, u;
long long arr[100010];
int main() {
	cin >> n >> m;
	arr[0] = n;
	switch (n) {
		case 1: {
			cin >> x;
			for (int i = 1; i <= m; i++) {
				arr[i] = arr[i-1] * x;
				arr[i] = (arr[i] % mod + mod) % mod;
			}
			break;
		}
		case 2: {
			cin >> x >> y;
			arr[1] = x;
			for (int i = 2; i <= m; i++) {
				arr[i] = arr[i-1] * x - arr[i-2] * y;
				arr[i] = (arr[i] % mod + mod) % mod;
			}
			break;
		}
		case 3: {
			cin >> x >> y >> z;
			arr[1] = x;
			arr[2] = x*x - 2*y;
			arr[2] = (arr[2] % mod + mod) % mod;
			for (int i = 3; i <= m; i++) {
				arr[i] = arr[i-1] * x - arr[i-2] * y + arr[i-3] * z;
				arr[i] = (arr[i] % mod + mod) % mod;
			}
			break;
		}
		case 4: {
			cin >> x >> y >> z >> u;
			arr[1] = x;
			arr[2] = x*x - 2*y;
			arr[2] = (arr[2] % mod + mod) % mod;
			arr[3] = (long long)x*x*x - 3*x*y + 3*z;
			arr[3] = (arr[3] % mod + mod) % mod;
			for (int i = 4; i <= m; i++) {
				arr[i] = arr[i-1] * x - arr[i-2] * y + arr[i-3] * z - arr[i-4] * u;
				arr[i] = (arr[i] % mod + mod) % mod;
			}
			break;
		}
	}
	cout << arr[m] << endl;
	return 0;
}
