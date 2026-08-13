#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
using namespace std; 

template <typename T> void in(T &x) {
    x = 0; T f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch)) {x = 10 * x + ch - 48; ch = getchar();}
    x *= f;
}

template <typename T> void out(T x) {
    if(x < 0) x = -x , putchar('-');
    if(x > 9) out(x/10);
    putchar(x%10 + 48);
}
//-------------------------------------------------------

const int N = 1e5+7,mod = 1e9+9;
int n;
ll b[N],ans;

struct node {
	int pos;ll sum;
}p[N];

struct map {
	int pos;ll sum;
	bool operator < (const map &x) const {
		return sum == x.sum ? pos < x.pos : sum < x.sum;//sum < x.sum;
	}
}a[N];

void A(int pos,ll k) {
	for(int i = pos;i <= n;i += i&-i) b[i] = (b[i]+k)%mod;
}

ll Q(int pos) {
	ll res = 0;
	for(int i = pos;i;i -= i&-i) res = (res + b[i])%mod;
	return res;
}

int main() {
	//freopen("0.in","r",stdin);
	//freopen("my.out","w",stdout);
	int i; ll x;
	in(n);
	a[0].pos = a[0].sum = 0;
	for(i = 1;i <= n; ++i) p[i].pos = i,in(x),p[i].sum = p[i-1].sum + x,a[i].pos = i,a[i].sum = p[i].sum;
	sort(a,a+n+1);//debug a[0]
	p[a[0].pos].sum = 1; int _id = 1;
	for(i = 1;i <= n; ++i) {
		if(a[i].sum != a[i-1].sum) ++_id;//debug i-1越界 
		p[a[i].pos].sum = _id;
	}
	//for(i = 1;i <= n; ++i) cout << p[i].sum << endl;
	A(p[0].sum,1);
	for(i = 1;i <= n; ++i) {
		ans = Q(p[i].sum);
		A(p[i].sum,ans);
		if(i == n) out(ans);
		//out(ans),putchar('\n');
	}
	//out(ans);
	return 0;
}
