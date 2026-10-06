// Source: https://www.luogu.com.cn/article/bijsyaaj
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
using namespace std;

constexpr int R = 5;
string rs[R];

inline void train() {
	   ios::sync_with_stdio(false);
	   cin.tie(0);
	   cout.tie(0);
}

int priority(char i) {
	switch (i) {
		case ')':
			return 4;
			break;
		case '#':
			return 3;
			break;
		case '&':
			return 2;
			break;
		case '+':
			return 1;
			break;
		case '(':
			return 0;
			break;
		default:	// -1 priority is usually for special uses
			return -1;
			break;
	}
}

inline void autopop(char i, stack<char> &op, stack<bool> &val) {
	bool res1, res2, res;
	while ((!op.empty()) && (priority(op.top()) >= priority(i))) {
		char t = op.top();
		switch (t) {
			case ')':
				break;
			case '(':
				if (i == ')') {
					op.pop();
					return;
				}
				break;	// Do nothing
			case '#':
				res = val.top();
				val.pop();
				val.push(!res);
				break;
			case '&':
				res2 = val.top();
				val.pop();
				res1 = val.top();
				val.pop();
				val.push(res1 && res2);
				break;
			case '+':
				res2 = val.top();
				val.pop();
				res1 = val.top();
				val.pop();
				val.push(res1 || res2);
				break;
		}
		op.pop();
	}
}

bool evaluate(string expr, map<char, bool> vals) {
	stack<char> op;
	stack<bool> val;
	for (auto &i : expr) {
		if (i >= 'a' && i <= 'h') {
			// Variable.
			val.push(vals[i]);
		} else {
			switch (i) {
				case '(':
					op.push('(');
					break;
				default:
					autopop(i, op, val);
					op.push(i);
			}
		}
	}
	autopop(' ', op, val);
	return val.top();
}

bool is_sames(string as, string bs, char op = '=', string cs = "") {
	for (int a = 0; a <= 1; a++) {
		for (int b = 0; b <= 1; b++) {
			for (int c = 0; c <= 1; c++) {
				for (int d = 0; d <= 1; d++) {
					for (int e = 0; e <= 1; e++) {
						for (int f = 0; f <= 1; f++) {
							for (int g = 0; g <= 1; g++) {
								for (int h = 0; h <= 1; h++) {
									map<char, bool> mp = {{'a', a}, {'b', b}, {'c', c}, {'d', d}, {'e', e}, {'f', f}, {'g', g}, {'h', h}};
									bool aexpr = evaluate(as, mp);
									bool bexpr = evaluate(bs, mp);
									bool cexpr;
									switch (op) {
										case '=':
											if (aexpr != bexpr) return false;
											break;
										case '#':
											if (aexpr == bexpr) return false;
											break;
										case '&':
											cexpr = evaluate(cs, mp);
											if (aexpr != (bexpr && cexpr)) return false;
											break;
										case '+':
											cexpr = evaluate(cs, mp);
											if (aexpr != (bexpr || cexpr)) return false;
											break;
									}
//									if (aexpr != bexpr) return false;
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

int stdmin = 114514, solu = -1;
vector<string> stdans;

int main() {

	train();
	
	for (int i = 0; i < 5; i++) cin>>rs[i];
	for (int i = 0; i < (1<<5); i++) {	// i bit 1: as stanard. i bit 0: not as stanard
		// You expect the smallest 1 counter
		
		vector<string> advanced;
		int stdcnt = 0;
		bool ok = true;
		for (int j = 0; j < 5; j++) {
			if ((1<<j) & i) {
				stdcnt++;
			} else {
				bool success = false;
				for (int s1 = 0; s1 < 5; s1++) {
					if ((1<<s1) & i) {
						if (is_sames(rs[j], rs[s1])) {
							advanced.push_back(string("R")+to_string(j+1)+string("=R")+to_string(s1+1));
							success = true;
							break;
						}
						if (is_sames(rs[j], rs[s1], '#')) {
							advanced.push_back(string("R")+to_string(j+1)+string("=#R")+to_string(s1+1));
							success = true;
							break;
						}
						bool flag = false;
						for (int s2 = 0; s2 < 5; s2++) {
							if ((1<<s2) & i) {
								if (is_sames(rs[j], rs[s1], '&', rs[s2])) {
									advanced.push_back(string("R")+to_string(j+1)+"=R"+to_string(s1+1)+"&R"+to_string(s2+1));
									flag = true;
									break;
								}
								if (is_sames(rs[j], rs[s1], '+', rs[s2])) {
									advanced.push_back(string("R")+to_string(j+1)+"=R"+to_string(s1+1)+"+R"+to_string(s2+1));
									flag = true;
									break;
								}
							}
						}
						if (flag) {
							success = true;
							break;
						}
					}
				}
				if (!success) {
					ok = false;
					break;
				}
			}
		}
		if (ok) {
			if (stdcnt < stdmin) {
				stdmin = stdcnt;
				solu = i;
				stdans = advanced;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (solu & (1<<i)) cout<<"R"<<(i+1)<<"\n";
	}
	for (auto &i : stdans) cout<<i<<"\n";
	
	cout<<flush;

	return 0;
}
