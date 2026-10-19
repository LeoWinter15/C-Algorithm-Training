// Source: https://www.luogu.com.cn/article/x2hl3qsy
#include <bits/stdc++.h>

using namespace std;

typedef complex<double> cp;

int n;
cp a[200005];
int p[100005];

double dj(cp x, cp y) {
	return x.real()*y.real() + x.imag()*y.imag();
}

double cj(cp x, cp y) {
	return x.real()*y.imag() - x.imag()*y.real();
}

bool chk(int ps) {
	auto dz = a[(ps+n/2-1)%n+1] - a[ps];
	for (int i = 1; i*2 < n; i++) {
		int ps1 = (ps+p[i]-1)%n+1;
		int ps2 = (ps-p[i]-1+n)%n+1;
		auto md = (a[ps1]+a[ps2]) / (double)2;
		if (cj(md-a[ps],dz) != 0 || dj(a[ps2]-a[ps1],dz) != 0) {
			return 0;
		}
	}
	return 1;
}

signed main() {
//	srand(time(0));
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d",&x);
			a[i*2+1].real(x);
			scanf("%d",&x);
			a[i*2+1].imag(x);
		}
		for (int i = 1; i < n; i++) {
			a[i*2] = (a[i*2-1] + a[i*2+1]) / (double)2;
		}
		a[n*2] = (a[1] + a[n*2-1]) / (double)2;
		for (int i = 1; i < n; i++) {
			p[i] = i;
		}
//		random_shuffle(p+1,p+n);
		int as = 0;
		n *= 2;
		for (int i = 1; i*2 <= n; i++) {
			if (chk(i)) {
				as++;
			}
		}
		cout << as << endl;
	}
	return 0;
}
