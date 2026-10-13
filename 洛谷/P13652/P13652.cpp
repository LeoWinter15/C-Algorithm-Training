// Source: https://www.luogu.com.cn/article/mjt4kcr2
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
using namespace std;
const int MAXN = 1e2 + 10;
const int inf = 0x3f3f3f3f;

int n,Cnt;
int dep[MAXN],fa[MAXN],deg[MAXN];
int a[MAXN],b[MAXN],cnt[MAXN],num=0,lf=0;
vector<int>G[MAXN];
PII e[MAXN];
bool us[MAXN],val[MAXN],vis[MAXN];

void dfs(int u,int fth){
	dep[u]=(fth!=-1?dep[fth]+1:0),fa[u]=fth;
	for(int v:G[u]){
		if(v==fth) continue;
		dfs(v,u);
	}
}

int main(){
	scanf("%d%d",&n,&Cnt);
	FL(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
		deg[u]++,deg[v]++;
	}
	FL(i,0,n-1){
		assert(deg[i]!=2);
		if(deg[i]==1) a[++lf]=i;
		else b[++num]=i,us[i]=1;
	}
	dfs(b[1],-1);
	if(Cnt>num){
		puts("DEFEND");
		FL(i,1,num) printf("%d ",b[i]);
		FL(i,num+1,Cnt) printf("%d ",a[i-num]),val[a[i-num]]=1;
		puts(""),fflush(stdout);
		int x,y;
		while(~scanf("%d",&x)&&x!=-1){
			if(us[x]||val[x]) puts("0"),fflush(stdout);
			else{
				vector<PII> Ed1,Ed2;
				FL(i,1,lf)
					if(val[a[i]]){val[a[i]]=0,val[x]=1,y=a[i];break;}
				while(dep[x]!=dep[y]){
					if(dep[x]>dep[y]) Ed1.push_back({fa[x],x}),x=fa[x];
					else Ed2.push_back({y,fa[y]}),y=fa[y];
				}
				while(x!=y){
					Ed1.push_back({fa[x],x}),x=fa[x];
					Ed2.push_back({y,fa[y]}),y=fa[y];
				}
				reverse(Ed2.begin(),Ed2.end());
				Ed1.insert(Ed1.end(),Ed2.begin(),Ed2.end());
				printf("%d\n",(int)Ed1.size());
				for(auto i:Ed1) printf("%d %d\n",i.first,i.second);
				fflush(stdout);
			}
		}
	}
	else{
		puts("ATTACK");
		fflush(stdout);
		FL(i,1,Cnt){
			int x;
			scanf("%d",&x);
			vis[x]=1;
		}
		while(1){
			int x=-1; 
			FL(u,0,n-1){
				bool fg=!vis[u];
				for(int v:G[u])
					if(vis[v]){fg=0;break;}	
				if(fg){x=u;break;}
			}
			if(x==-1){
				int mn=inf;
				FL(u,0,n-1)
					if(!vis[u]&&deg[u]==1&&cnt[u]<mn) mn=cnt[u],x=u;
			}
			cnt[x]++;
			printf("%d\n",x);
			fflush(stdout);
			int K;
			if(scanf("%d",&K)!=1) exit(0);
			FL(i,1,K) scanf("%d%d",&e[i].first,&e[i].second);
			FL(i,1,K) vis[e[i].first]=0;
			FL(i,1,K) vis[e[i].second]=1;
		}
	}
}
