#include<bits/stdc++.h>
#define ll long long 
#define re read()
#define mm 400009
#define w qwrite
#define gc getchar()	
using namespace std;
//定义区
struct node{
	int a,b;
    bool operator <( const node & x)const
    {
        return x.a<a;//从大到小
    }
}len[mm];
struct nihao {
	int fre,l,r,sum;//历史的树根节点，左子树，右子树(都是指的节点)//某个区间有几个数 
	int Sum;//原数组的值 
}t[mm<<4];
int b[mm];//原数组，离散数组 
int nodee;//节点
int inst;//修改插入的点
int g;//离散的右边界 
int tok[mm];
int n,m,c,kk; 
int f,anss=-1;
ll ans1,ans2;
//函数区
int read(){//int ull
	int x=0,y=1; char s=gc;if(s=='-')y=-1;
	while(!isdigit(s))s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+s-'0',s=gc;
	return x*y;
} 

void qwrite(int x)
{
    if(x==0){putchar('0');puts("");return ;}
	int cnt=0,u[400];
	if(x<0) x=-x,putchar('-');
	while(x){u[cnt++]=x%10;x/=10;}
	while(cnt--) putchar(u[cnt]+'0');puts("");
}

void make(int &x,int l,int r)//建树 
{
	x=++nodee;
	if(l==r)return ;//叶节点
	int mid=(l+r)>>1;
	make(t[x].l,l,mid);
	make(t[x].r,mid+1,r); 
	return ;
}

int modify(int x,int l,int r)
{
	int xi=++nodee;//建立新节点
	t[xi].l=t[x].l;t[xi].r=t[x].r;t[xi].sum=t[x].sum+1;t[xi].Sum+=t[x].Sum+b[inst];//传递树节点数据
	if(l==r)return xi;//已经到叶节点，不用再建树了
	int mid=(l+r)>>1;
	if(inst<=mid) t[xi].l=modify(t[xi].l,l,mid);//对于这个数比这个区间小就到左边，右边同理
	else  t[xi].r=modify(t[xi].r,mid+1,r);
	return xi; 
} 

int query(int use,int now,int l,int r,int k)
{
	 ll  ans=0;
	int mid=(l+r)>>1;
	int h=t[t[now].l].sum-t[t[use].l].sum;//h是权值线段树操作
		if(l==r){    return k*b[l];//奖学金有一样的，只要这个节点的k个人！！！ 
	}
	 if(k<=h)ans+=query(t[use].l,t[now].l,l,mid,k);//递归的都是节点 
	 else 
	 {
	    ans+=t[t[now].l].Sum-t[t[use].l].Sum;//加上查过的数 
	 	ans+=query(t[use].r,t[now].r,mid+1,r,k-h);//注意要减去左区间的数 
	 }
	 return ans; 
}

signed main ()
{
    int l,r;
    n=re,c=re,f=re;kk=n/2;
    for(int i=1;i<=c;i++)len[i].a=re,len[i].b=re,b[i]=len[i].b;
    sort(len+1,len+1+c); //重载过了
    sort(b+1,b+c+1);
    g=unique(b+1,b+c+1)-b-1;

	make(t[0].fre,1,g);
	for(int i=1;i<=c;i++)//全部建树
	{
		inst=lower_bound(b+1,b+g+1,len[i].b)-b;//找到a[i]对应的离散化下标
		t[i].fre=modify(t[i-1].fre,1,g);//基于上一个版本的树 
	} 
	for(int i=1+(n-1)/2;i<=c-(n/2);i++)
	{
		ans1=query(t[0].fre,t[i-1].fre,1,g,kk);
		ans2=query(t[i].fre,t[c].fre,1,g,kk);
		if(ans1+ans2+len[i].b<=f)anss=max(anss,len[i].a);
		if(anss!=-1)break;
	}
	w(anss);
    return 0;
}
