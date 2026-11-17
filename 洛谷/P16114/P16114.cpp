// Source: https://www.luogu.com.cn/article/etjci1fu
/*
 * author: LostKeyToReach
 * created time: 2026-04-04 14:03:02
 */
#include <bits/stdc++.h>
#define int long long
#define vi std::vector<int>
#define eb emplace_back
using ll = long long;
using pii = std::pair<int, int>;
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define chkmax(x, y) x = std::max(x, y)
#define chkmin(x, y) x = std::min(x, y)
int fio = (std::cin.tie(0)->sync_with_stdio(0), 0);
constexpr int N = 5e5 + 5;
bool f[N][2][2], g[N][2][2];
std::string s;
bool check(int i, int x, int y, int z) {
    if (s[i] == '*') return 1;
    return x + y + z == s[i] - '0' - (s[i - 1] == '*') - (s[i + 1] == '*');
}
int32_t main() {
    int t; std::cin >> t;
    while (t--) {
        // std::string s;
        std::cin >> s; s = " " + s;
        int n = sz(s) - 1;
        for (int i = 1; i <= n + 1; ++i)
            for (int x = 0; x < 2; ++x)
                for (int y = 0; y < 2; ++y)
                    f[i][x][y] = g[i][x][y] = 0;
        f[1][0][0] = f[1][0][1] = 1;
        for (int i = 1; i <= n; ++i)
            for (int x = 0; x < 2; ++x)
                for (int y = 0; y < 2; ++y)
                    for (int z = 0; z < 2 - (i == n); ++z)
                        f[i + 1][y][z] |= check(i, x, y, z) & f[i][x][y];
        g[n + 1][0][0] = g[n + 1][1][0] = 1;
        for (int i = n; i >= 1; --i)
            for (int x = 0; x < 2; ++x)
                for (int y = 0; y < 2; ++y)
                    for (int z = 0; z < 2 - (i == n); ++z)
                        g[i][x][y] |= check(i, x, y, z) & g[i + 1][y][z];
        for (int i = 1; i <= n; ++i) {
            bool a = 0, b = 0;
            for (int x = 0; x < 2; ++x)
                a |= f[i][x][0] & g[i][x][0], b |= f[i][x][1] & g[i][x][1];
            if (a && b) std::cout << "?";
            else if (b) std::cout << "*";
            else std::cout << ".";
        }
        std::cout << "\n";
    }
}
