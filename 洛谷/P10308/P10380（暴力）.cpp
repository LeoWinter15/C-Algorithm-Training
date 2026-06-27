/*
往第 i（1 <= i <= m）位填 j（0 <= j <= n） 的方案数有 C(n-j+m-2,m-2)
贡献为 i!*C(n-j+m-2,m-2) 
*/ 
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int n, m, P;
int fac[N], inv[N], a[N], ans = 0;
int sum[N];
int qpow(int a, int b){
	int res = 1, base = a;
	while (b){
		if (b & 1) res *= base;
		base *= base;
		res %= P;
		base %= P;
		b >>= 1;
	}
	return res;
}
int C(int n, int m){
	return fac[n] * inv[n - m] % P * inv[m] % P;
}
int Lucas(int n, int m){
	if (m == 0) return 1;
	return Lucas(n / P, m / P) * C(n % P, m % P) % P;
}
signed main(){
	cin >> n >> m >> P;
	fac[0] = fac[1] = inv[0] = inv[1] = sum[1] = 1;
	for (int i = 2; i <= N - 5; i ++){
		fac[i] = fac[i - 1] * i % P;
		sum[i] = (sum[i - 1] + fac[i]) % P;
		inv[i] = (P - P / i) * inv[P % i] % P;
	}
	for (int i = 1; i <= N - 5; i ++){
		inv[i] = inv[i - 1] * inv[i] % P;
	}
	if (m == 1){
		cout << n % P << "\n";
		return 0;
	}
//	cout << sum[m] << "\n";
//	for (int i = 1; i <= m; i ++){
		for (int j = 1; j <= n; j ++){
			int now = Lucas(m - 2 + n - j, m - 2);
			ans += (sum[m] * j % P * now % P);
			ans %= P;
//			cout << ans << " ";
		}
//		cout << "\n";
//	}
	cout << ans % P << "\n";
	return 0;
} 
