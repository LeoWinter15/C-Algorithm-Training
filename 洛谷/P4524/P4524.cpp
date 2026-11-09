// Source: https://www.luogu.com.cn/article/jw25w1cs
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2005,INF=1e16;

int n,m; 
vector<tuple<int,int,int>> vec[N];

struct Node {
	int u,w1,w2;
	inline bool operator < (const Node& b) const {
		return w1*w2 > b.w1*b.w2;
	}
};

priority_queue<Node> que;
int dis[N];
set<pair<int,int>> S[N]; // 维护凸包 

void dij(int s) {
	que.push({s,0,0});
	memset(dis,63,sizeof(dis));
	S[s].insert({0,0});
	
	int v1,v2;
	while(!que.empty()) {
		auto [u,p,q]=que.top();
		que.pop();
		
		if(!S[u].count({p,q})) continue;
		dis[u]=min(dis[u],p*q);
		
		for(auto& [v,w1,w2]:vec[u]) {
			v1=p+w1,v2=q+w2;
			auto p=S[v].lower_bound({v1,v2});
			if(p!=S[v].begin() && (*prev(p)).second<v2) continue; // 无法更新
			while(p!=S[v].end() && (*p).second>v2) p=S[v].erase(p);
			S[v].insert({v1,v2});
			que.push({v,v1,v2});
		}
	}
}

signed main() {
	cin >> n >> m;
	
	int u,v,w1,w2;
	for(int i=1;i<=m;++i) {
		cin >> u >> v >> w1 >> w2;
		vec[u].push_back(make_tuple(v,w1,w2));
		vec[v].push_back(make_tuple(u,w1,w2));
	}
	
	dij(1);
	
	for(int i=2;i<=n;++i) {
		if(dis[i]<=INF) cout << dis[i] << endl;
		else cout << -1 << endl;
	}
	return 0;
}
