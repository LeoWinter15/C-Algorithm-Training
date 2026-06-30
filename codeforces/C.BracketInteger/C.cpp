#include <bits/stdc++.h>
using namespace std;

string s, ans;
int n;

bool dfs(int pos, bool less, vector<int>& st) {
    if (pos == n) return true;
    int L = n - pos - 1;
    int high = less ? 9 : (s[pos] - '0');
    int low = (pos == 0) ? 1 : 0;  // 最高位不能为0
    for (int x = high; x >= low; --x) {
        bool pushed = false;
        if (!st.empty() && st.back() == x) {
            st.pop_back();
        } else {
            st.push_back(x);
            pushed = true;
        }
        if ((int)st.size() <= L && (L - (int)st.size()) % 2 == 0) {
            ans[pos] = char('0' + x);
            if (dfs(pos + 1, less || (x < s[pos] - '0'), st)) {
                return true;
            }
        }
        // 撤销操作
        if (pushed) st.pop_back();
        else st.push_back(x);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        n = (int)s.size();
        if (n % 2 == 1) {
            cout << string(n - 1, '9') << '\n';
            continue;
        }
        ans.assign(n, ' ');
        vector<int> st;
        if (dfs(0, false, st)) {
            cout << ans << '\n';
        } else {
            cout << string(n - 2, '9') << '\n';
        }
    }
    return 0;
}