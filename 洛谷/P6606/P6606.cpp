// Source: https://www.luogu.com.cn/article/xr5k1j05
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define _ read<int>()
template <class T>T read()
{
	T r=0,f=1;char c=getchar();
	while((c>'9'||c<'0')&&c!='-') c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(c>='0'&&c<='9') r=r*10+c-'0',c=getchar();
	return f*r;
}
inline void out(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x<10) putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int maxn=1e6+5,mod=998244353;
int n,m,head[maxn],cnt,ans;
int len[maxn];
bool vis[maxn];
char s[24*maxn];
string str;
struct node
{
    int to,next;
}e[maxn<<1];
void add(int u,int v)//链式前向星
{

    e[++cnt].next=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
void dfs(int son,int dis)//dfs
{
    len[son]=dis;
    set<int> se;
    for(int i=head[son];i;i=e[i].next)
	{
        se.insert(e[i].to);
    }
    for(set<int>::iterator ite=se.begin();ite!=se.end();ite++)
	{
        if(!vis[*ite])
		{
            vis[*ite]=1;
            dfs(*ite,(dis*1000000+*ite)%mod);
        }
    }
}
signed main()
{
    memset(len,-1,sizeof(len));
	n=_,m=_;
    scanf("%s",s+1);
    int d=strlen(s+1);
    for(int i=1;i<=d;i+=12)
	{
        int v=0,u=0;
        for(int j=i;j<=i+11;j++)
		{
            if(j<i+6)
			{
                v=v*10+s[j]-'0';
            }
			else
			{
                u=u*10+s[j]-'0';
            }
        }
        add(v,u),add(u,v);
    }
    vis[0]=1;
    dfs(0,0);
    for(int i=1;i<n;i++)
	{
		out(len[i]);
        putchar('\n');
    }
    return 0;
}
