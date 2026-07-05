#include <bits/stdc++.h>
using namespace std;
int N, P;
int s = 0;//s指所选稻草人的防御力总和
int A[500005];
priority_queue<int, vector<int>, greater<int> >q;
//小根堆
int main() {
	cin >> N >> P;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}
	for (int i = 1; i <= N; i++) {
		s += A[i];
		q.push(A[i]);//添加第 i 个稻草人的防御力
		while (q.size() && s - q.top() >= P) {
			int tmp = q.top();
			q.pop();
			s -= tmp;
      //取出所选稻草人中防御力最小的
		}
		if (s < P) cout << -1 << ' ';//如果所有的选择的稻草人的防御力小于箭力量 P，那么输出 -1
		else cout << q.size() << ' ';
	}
	return 0;
}
