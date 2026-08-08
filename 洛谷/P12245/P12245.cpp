#include<bits/stdc++.h>
using namespace std;
int n, m, a[505][505], com[505][505], mx[505], ans;
int main() {
    // 输入数据
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    // 计算每对学生的共同兴趣数
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++)
                if (a[i][k] && a[j][k])  // 如果两人都对活动k感兴趣
                    com[i][j]++;
    // 找出每个学生与其他学生的最大共同兴趣数
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)  // 不能和自己比较
                mx[i] = max(mx[i], com[i][j]);
    // 枚举所有可能的修改方案：k=-1表示不修改，k>=0表示修改第k项活动
    for (int k = -1; k < m; k++) {
        // 如果要修改的活动k已经是小O感兴趣的，跳过
        if (k >= 0 && a[0][k]) continue;
        int cnt = 0;  // 统计当前方案下向小O发出邀约的人数
        // 检查每个学生是否会向小O发出邀约
        for (int i = 1; i < n; i++) {
            int cur = com[0][i];  // 初始共同兴趣数
            // 如果修改了活动k且学生i对活动k感兴趣，共同兴趣数+1
            if (k >= 0 && a[i][k]) cur++;
            // 如果共同兴趣数达到或超过学生i的最大值，会向小O发出邀约
            if (cur >= mx[i]) cnt++;
        }
        // 更新最大邀约人数
        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}
