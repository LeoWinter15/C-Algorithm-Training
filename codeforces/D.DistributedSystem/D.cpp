#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    long long base = 0;                // subtasks from full cycles
    vector<long long> diff(n + 1, 0);  // difference array for remainder

    while (q--) {
        long long a;
        int b;
        cin >> a >> b;

        base += a / n;
        int rem = a % n;
        if (rem == 0) continue;

        // add 1 to range [b, b+rem-1] modulo n
        int l = b;
        int r = b + rem;
        if (r <= n) {
            diff[l] += 1;
            diff[r] -= 1;
        } else {
            diff[l] += 1;
            diff[0] += 1;
            diff[r - n] -= 1;
        }
    }

    vector<long long> ans(n);
    long long cur = 0;
    for (int i = 0; i < n; ++i) {
        cur += diff[i];
        ans[i] = base + cur;
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
