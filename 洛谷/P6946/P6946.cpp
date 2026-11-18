// Source: https://www.luogu.com.cn/article/iv49ksgx
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const int MAXM = 3000;
char str[MAXN];
int n, len[MAXM], sum, maxx, cnt[MAXN * MAXM], ans, ansx, aa[MAXM], bb[MAXM];
int G[MAXM]; 
bool used[MAXN * MAXM];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str + 1;
		len[i] = strlen(str + 1);
		maxx = max(maxx, len[i]); 
		sum += len[i];
	}	
	for (int gap = maxx; gap < sum + n; gap++) {
		int maxx = 0;
		int j = 1, Len = 0, eid1 = 0, eid = 0;
		int len1 = 0, len2 = 0;
		while (j <= n) {
			++eid1;
			while (Len + len[j] <= gap && j <= n) {
				Len = Len + len[j] + 1;
				if (Len + len[j + 1] <= gap && j < n) {
					G[++eid] = Len;
					bb[++len2] = Len;
					int A = 0;
					if (used[Len - 1]) A = max(A, cnt[Len - 1]);
					if (used[Len]) A = max(A, cnt[Len]); 
					if (used[Len + 1]) A = max(A, cnt[Len + 1]);
					cnt[Len] = A + 1;
					maxx = max(maxx, cnt[Len]);
				}
				j++;
			}
			Len = 0;
			for (int i = 1; i <= len1; i++) used[aa[i]] = false;
			for (int i = 1; i <= len2; i++) used[bb[i]] = true;
			len1 = len2;
			for (int i = 1; i <= len2; i++) aa[i] = bb[i];
			len2 = 0;
		}
		for (int i = 1; i <= len1; i++) used[aa[i]] = false;
		for (int i = 1; i <= eid; i++) cnt[G[i]] = 0;
		if (maxx > ans) {
			ans = maxx;
			ansx = gap;
		}
	}
	cout << ansx << " " << ans << endl;
	return 0;
}
