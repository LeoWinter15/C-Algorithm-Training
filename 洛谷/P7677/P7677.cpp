// Source: https://www.luogu.com.cn/article/u3lfu1u1
#include<iostream>
using namespace std;
int n,l;
const int N=3e5+5;
int vis[N],fa[N];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void un(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)
		fa[y]=x;
}//并查集基本操作 
int main(){
	cin>>n>>l;
	for(int i=1;i<=l;i++)fa[i]=i;//初始化 
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		if(vis[find(x)]==0||vis[find(y)]==0) {//放得下 
			cout<<"LADICA\n";
			if(vis[find(x)]==0){//可以执行条件1/3 
				vis[find(x)]=1;//标记 
				un(y,x);
			}
			else{//可以执行条件2/4 
				vis[find(y)]=1;//标记 
				un(x,y);
			}
		} 
		else cout<<"SMECE\n";//放不下 
	}
	return 0; 
}
