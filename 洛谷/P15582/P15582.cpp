// Source: https://www.luogu.com.cn/article/3enhb6iy
#include<bits/stdc++.h>
using namespace std;

#define PII pair<int,int>
#define fi first
#define se second 

int a[100005], n;

// 线段树代码略，请参考上文

bool is[20][100005];
long long ans;
int dep[100005], lenth[20], druzewang;

bool check(int x, int l, int r) { // check 是否是中点唯一最大 并且 左右儿子都合法 
    if (r == l)
        return true;
    PII checker = qry(1, l, r);
    int Dep = dep[r - l + 1];
    int lst_len = lenth[Dep - 1];
    return (checker.se == 1 && checker.fi == a[x] && is[Dep - 1][l] && is[Dep - 1][l + lst_len + 1]);
}

long long initialize(int N, vector<int> A) {
    reverse(A.begin(), A.end());
    A.push_back(0);
    reverse(A.begin(), A.end());
    ans = n = N;
    for (int i = 1; i <= n; ++i) {
        a[i] = A[i];
        is[0][i] = true;
    }
    build(1, 1, n);
    long long len = 3, lst_len = 1;
    lenth[0] = 1;
    dep[1] = 0;
    for (int i = 1; len <= n; ++i) {
        lenth[dep[len] = i] = len;
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            if (check(l + r >> 1, l, r))
                ++ans, is[i][l] = true;
        }
        lst_len = len;
        len = len << 1 | 1;
        druzewang = i;
    }
    return ans;
}

void dfs(int pos, int l, int r, int dep) {
    int len = r - l + 1;
    int new_mid = r + 1;
    int new_r = new_mid + len;
    if (new_r <= n) {
        bool flag = check(new_mid, l, new_r);
        if (flag ^ is[dep + 1][l]) {
            if (flag) ++ans;
            else --ans;
            is[dep + 1][l] = flag;
            dfs(new_mid, l, new_r, dep + 1);
        }
    }
    new_mid = l - 1;
    int new_l = new_mid - len;
    if (new_l > 0) {
        bool flag = check(new_mid, new_l, r);
        if (flag ^ is[dep + 1][new_l]) {
            if (flag) ++ans;
            else --ans;
            is[dep + 1][new_l] = flag;
            dfs(new_mid, new_l, r, dep + 1);
        }
    }
}

long long update_sequence(int p, int v) {
    ++p;
    update(1, p, v);
    a[p] = v;
    int len = 1, lst_len = 0;
    for (int i = 0; len <= n; ++i) {
        int l = p - lst_len, r = p + lst_len;
        if (l < 1 || r > n)
            break;
        bool flag = check(p, l, r);
        if (is[i][l] ^ flag) {
            if (flag) ++ans;
            else --ans;
            is[i][l] = flag;
        }
        dfs(p, l, r, i);
        lst_len = len;
        len = len << 1 | 1;
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    int n, q; cin >> n >> q;
    vector<int> A;
    A.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    cout << initialize(n, A) << '\n';
    for (int cases = 1; cases <= q; ++cases) {
        int p, v;
        cin >> p >> v;
        A[p] = v;
        cout << update_sequence(p, v) << '\n';
    }
}
