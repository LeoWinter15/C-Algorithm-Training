// Source: https://www.luogu.com.cn/article/4hw5posx
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int T;
long long m;
priority_queue<long long, vector<long long>, greater<long long> > pq;
bool check(long long x) {
	while(x % 2 == 0) x /= 2;
	return x == 1;
}
int main() {
	cin >> T;
	for(int ti = 1; ti <= T; ti++) {
		cin >> m;
		for(long long i = (1ll << 62); i >= 1; i >>= 1) {
			if(m >= i) m -= i, pq.push(i);
		}
		int ct1 = 0;
		while(!check(pq.size() + ct1)) {
			int num = pq.top();
			pq.pop();
			if(num == 1) ct1++;
			else {
				pq.push(num / 2);
				pq.push(num / 2);
			}
		}
		for(int i = 1; i <= ct1; i++) {
			printf("1 ");
		}
		while(!pq.empty()) {
			printf("%lld ", pq.top());
			pq.pop();
		}
		puts("");
	}
	return 0;
}
