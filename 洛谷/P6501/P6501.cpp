#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int x=0,f=1;re char ch=getchar();
	while(!(ch>='0'&&ch<='9')&&ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void fput(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)fput(x/10);
	putchar(x%10+'0');
	return ;
}
#define N 305
#define M 40005
#define inf N
int n,m,k,head[M],cnt=1;
struct node{//链式前向星存储有向边,w表示流量,c表示费用 
	int to,nxt,w;
	double c;
}a[M];
inline void addedge(int u,int v,int w,double c){
	a[++cnt]=node{v,head[u],w,c};head[u]=cnt;
	a[++cnt]=node{u,head[v],0,-c};head[v]=cnt;
	return ;
}
int s,t;
//起点:1
//选手:2~n+1
//比赛:n+2~n+m+1
//比赛汇合点:n+m+2
//终点:n+m+3 
double dis[N];
queue<int>q;
bool vis[M];
const double eps=1e-6;
int now[M];
inline bool bfs(){//SPFA 
	for(re int i=s;i<=t;i++){
		dis[i]=DBL_MAX;now[i]=head[i];
	}
	dis[s]=0.0;
	q.push(s);
	while(!q.empty()){
		re int x=q.front();q.pop();vis[x]=0;
		for(re int i=head[x];i;i=a[i].nxt){
			if(a[i].w&&dis[a[i].to]>dis[x]+a[i].c){
				dis[a[i].to]=dis[x]+a[i].c;
				if(!vis[a[i].to]){
					q.push(a[i].to);
					vis[a[i].to]=1;
				}
			}
		}
	}
	return fabs(dis[t]-DBL_MAX)>eps;
}
double cost;
int dfs(int x,int flow){//dinic
	if(x==t||!flow)return flow;
	re int add=0;vis[x]=1;
	for(re int i=now[x];i;i=a[i].nxt){
		now[x]=i;
		if(!vis[a[i].to]&&a[i].w&&dis[a[i].to]==dis[x]+a[i].c){
			re int res=dfs(a[i].to,min(flow,a[i].w));
			if(res){
				flow-=res;
				add+=res;
				a[i].w-=res;
				a[i^1].w+=res;
				cost+=a[i].c*res;
				if(!flow)break;
			}
		}
	}
	vis[x]=0;
	return add;
}
int main(){
	n=read();m=read();k=read();
	s=1;t=n+m+3;
	for(re int i=1;i<=n;i++){//超级源点向选手连边 
		addedge(s,i+1,1,0.0);
	}
	for(re int i=1;i<=m;i++){//选手与比赛之间连边 
		for(re int j=1,id;j<=n;j++){
			id=read();
			re double c;
			scanf("%lf",&c);
			addedge(id+1,i+n+1,1,-c);
		}
		addedge(i+n+1,n+m+2,inf,0.0);//比赛向第一汇点连边 
	}
	addedge(n+m+2,n+m+3,k,0.0);//第一汇点向第二汇点连边 
	re int ans=0;
	while(bfs()){//最小费用最大流 
		ans+=dfs(s,INT_MAX);
	}
	printf("%.1f",-cost);//答案取相反数,保留一位小数 
	return 0;
}
