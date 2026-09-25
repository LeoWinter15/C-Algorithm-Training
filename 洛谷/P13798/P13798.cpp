#include<bits/stdc++.h>
using namespace std;
#define __MY_TEST__ 0
#define double long double
inline int read()
{
	int f=1,re=0;
	char ch=getchar();
	while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar();}
	while( isdigit(ch)) re=(re<<3)+(re<<1)+(ch^'0'),ch=getchar();
	return re*f;
}
const double eps=1e-9;
const int N=1e7+5;
struct line
{
	double k,b;
    double operator ()(double x)
    {
        return k*x+b;
    }
}node[N<<2];
int cnt;
int tot,tree[N<<2],ls[N<<2],rs[N<<2],rt;
int cmp(double x,double y)
{
	if(x-y>eps) return 1;
	if(y-x>eps) return -1;
	return 0;
}
double calc(int num,double x)
{
	return node[num].k*x+node[num].b;
}
void add(int x0,int y0,int x1,int y1)
{
	cnt++;
	if(x0==x1)
	{
		node[cnt].k=0,node[cnt].b=max(y0,y1);
	}
	else
	{
		node[cnt].k=(y1-y0)*1.0/(x1-x0);
		node[cnt].b=y0-node[cnt].k*x0;
	}
}
void update(int &num,int l,int r,int x)
{
    if(!num) num=++tot;
    if(!tree[num])
    {
        tree[num]=x;
        return ;
    }
	int mid=(l+r)>>1,&y=tree[num];
	int pmid=cmp(calc(x,mid),calc(y,mid));
	if(pmid==1||(!pmid&&x<y)) swap(x,y);
	int pl=cmp(calc(x,l),calc(y,l)),pr=cmp(calc(x,r),calc(y,r));
	if(pl==1||(!pl&&x<y)) update(ls[num],l,mid,x);
	if(pr==1||(!pr&&x<y)) update(rs[num],mid+1,r,x);
}
pair<double,int>maxp(pair<double,int>x,pair<double,int>y)
{
	if(cmp(x.first,y.first)==-1)
	{
		return y;
	}
	else if(cmp(x.first,y.first)==1) return x;
	return x.second<y.second?x:y;
}
pair<double,int>query(int num,int l,int r,double pos)
{
	if(!num||l>pos||r<pos) return make_pair(-1e16,0);
	int mid=(l+r)>>1;
	double re=calc(tree[num],pos);
	if(l==r)
	{
		return make_pair(re,tree[num]);
	}
	return maxp(make_pair(re,tree[num]),maxp(query(ls[num],l,mid,pos),query(rs[num],mid+1,r,pos)));
}
signed main()
{
#if __MY_TEST__
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        int t=read(),p=read();
        cnt++;
        node[cnt].k=(t-p)/100000000.0;
        node[cnt].b=p;
        update(rt,0,100000000,cnt);
    }
    for(int i=1;i<=m;i++)
    {
        int t=read(),p=read();
        double x=t*100000000.0/(t+p);
        auto re=query(rt,0,100000000,x);
        cout<<re.second<<'\n';
    }
}

