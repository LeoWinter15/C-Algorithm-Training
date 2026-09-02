#include<bits/stdc++.h>
using namespace std;

const int N = 60;
string p[N], e[N];
int va[N], rt[N], t[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n = 0;
	while (getline(cin, p[n+1])) {
		++n;
		if (p[n][p[n].size()-1] == '\r') p[n].pop_back();
		if (p[n][p[n].size()-1] == ' ') p[n].pop_back();
	}
	int tp = 1;
	for (int i = 6; i < p[1].size(); i += 2) va[1] |= 1<<(p[1][i]-'A');
	for (int i = 2; i <= n; i++) {
		string s = p[i];
		int v = 0, r = 0;
		for (int i = 1; i <= tp; i++) {
			if (i < tp && t[i+1]) continue;
			v |= va[i], r |= rt[i];
		}
		if (s == "END IF") {
			if (t[tp]) {
				va[tp-2] |= (va[tp] | rt[tp]) & (va[tp-1] | rt[tp-1]);
				rt[tp-2] |= rt[tp] & rt[tp-1];
				tp -= 2;
			} else --tp;
		} else if (s == "ELSE") va[++tp] = 0, rt[tp] = 0, t[tp] = 1;
		else if (s.substr(0, 2) == "IF") {
			va[++tp] = 0, rt[tp] = 0, t[tp] = 0;
			if (!(v & (1<<(s[3]-'A')))) e[i] = s[3];
			if (s[7] >= 'A' && s[7] <= 'Z' && !(v & (1<<(s[7]-'A')))) e[i] += s[7];
		} else if (s.substr(0, 6) == "RETURN") {
			if (s[7] >= 'A' && s[7] <= 'Z' && !(v & (1<<(s[7]-'A')))) e[i] = s[7];
			rt[tp] = 0xfffffff;
		} else {
			va[tp] |= 1<<(s[0]-'A');
			for (int j = 1; j < s.size(); j++) {
				if (s[j] >= 'A' && s[j] <= 'Z' && !(v & (1<<(s[j]-'A')))) e[i] += s[j];
			}
		}
		if (r && s != "END IF" && s != "ELSE") e[i] = "#";
	}
	for (int i = 1; i <= n; i++) {
		if (e[i] == "#") cout << "Line " << i << ": unreachable code\n";
		else {
			sort(e[i].begin(), e[i].end()); 
			e[i].erase(unique(e[i].begin(), e[i].end()), e[i].end());
			for (char c : e[i]) {
				cout << "Line " << i << ": variable " << c << " might not have been initialized\n";
			}
		}
	}
	return 0;
}
