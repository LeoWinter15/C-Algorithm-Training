#include <bits/stdc++.h>
using namespace std;
int n, as = 0;
vector<vector<int>> m;
vector<vector<bool>> u;

//计算以(i,j)为左上角的3x3子矩阵的和
int cs(int i, int j) {
    int sum = 0;
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            sum += m[i+x][j+y];
    return sum;
}

//检查以(i,j)为左上角的3x3子矩阵是否可用
bool ck(int i, int j) {
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            if (u[i+x][j+y]) return false;
    return true;
}

//标记或取消标记3x3子矩阵
void m1(int i, int j, bool f) {
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            u[i+x][j+y] = f;
}

//递归枚举所有可能的子矩阵组合
void d(int i, int j, int c) {
    if (j > n-3) { j = 0; i++; }      //换行
    if (i > n-3) {      //遍历完所有可能位置 
        as = max(as, c);
        return;
    }

//不选当前位置的子矩阵
    d(i, j+1, c);

//如果可以选当前位置的子矩阵
    if (ck(i, j)) {
        int sum = cs(i, j);
        m1(i, j, true);
        d(i, j+1, c + sum);
        m1(i, j, false);
    }
}

int main() {
    cin >> n;
    m.resize(n, vector<int>(n));
    u.resize(n, vector<bool>(n, false));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> m[i][j];
    
    if (n >= 3){
        d(0, 0, 0);
    } 
    cout << as << endl;
    return 0;
}
