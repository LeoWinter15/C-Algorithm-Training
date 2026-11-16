// Source: https://www.luogu.com.cn/article/460jk4gx
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using pii = pair<int, int>;
#define mr make_pair
#define fi first
#define se second
using vi = vector<int>; using vii = vector<pii>;
#define pb emplace_back
#define sz(x) ((int)(x).size())
template<class T, class U> inline void cmn(T &x, const U &y) { if(y < x) x = y; }
template<class T, class U> inline void cmx(T &x, const U &y) { if(y > x) x = y; }
const char nl = '\n', nk = ' ';
const int inf = sizeof(int) == 4 ? 0x3f3f3f3f : 0x3f3f3f3f3f3f3f3f;

mt19937 rng(19171107);
int rnd(int l, int r) { return uniform_int_distribution<>(l, r)(rng); }
db rndb(db l, db r) { return uniform_real_distribution<>(l, r)(rng); }

const int N = 1010;

int n;
ll a[N];
int p[N];

ll res;

void calc(int x, int v) {
  int A = p[x > 2 ? x - 2 : x + n - 2], B = p[x > 1 ? x - 1 : n], &C = p[x], D = p[x < n ? x + 1 : 1], E = p[x < n - 1 ? x + 2 : x + 2 - n];
  res -= (a[A] * a[B] * B + a[B] * C * a[D] + D * a[D] * a[E]) * a[C];
  C = v;
  res += (a[A] * a[B] * B + a[B] * C * a[D] + D * a[D] * a[E]) * a[C];
}

void SA(db t0, db te, db dt) {
  res = 0;
  for(int i = 1; i <= n; ++i) calc(i, i);
  for(db t = t0; t >= te; t *= dt) {
    int x = rnd(1, n), y = rnd(1, n);
    ll ores = res;
    int px = p[x], py = p[y];
    calc(y, px), calc(x, py);
    if(res > ores || rndb(0, 1) <= exp((res - ores) / t));
    else res = ores, swap(p[x], p[y]);
//    cerr << t << ": " << res << nl;
  }
  cerr << "res = " << res << nl;
  for(int i = 1; i <= n; ++i) cout << p[i] << (i == n ? nl : nk);
}

void mian() {
  cin >> n;
  for(int i = 1; i <= n; ++i) cin >> a[i];
  SA(1e15, 1e-15, 0.99999999);
}

signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
//  cin >> t;
  while(t--) mian();
  return 0;
}
