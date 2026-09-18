#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const long long N=20009;
const long long mod=998244353;
long long n,a[N],tot,len;
long long top1,q[N];
long long stack_fu[N],top2,dian;
long long stack_num[N];
char s[N];
long long ls[N],rs[N];//后缀表达式树左右儿子
struct node
{
    long long len;
    long long a[1009];
} ss[N][2],tr[N]; //高精度数组，结构体更方便赋值
bool check(long long x,long long y)//判断优先级
{
    if(ss[x][1].len==-4) return 0;
    if(ss[x][0].len>ss[y][0].len) return 1;
    if(ss[x][0].len<ss[y][0].len) return 0;
    if(a[ss[x][0].len]==0) return 1;
    else return 0;
}
long long power(long long a,long long b,long long Mod)
{
    if(a==0&&b==0) return 1;
    long long ans=1,base=a%Mod;
    while(b)
    {
        if(b&1) ans=(ans*base)%Mod;
        base=(base*base)%Mod;
        b>>=1;
    }
    return ans;
}
long long check_power(long long a,
                      long long b)//时时判断b是否超出了mod来预处理数组q
{
    if(a==0&&b==0) return 1;
    long long ans=1,base=a;
    while(b)
    {
        if(b&1)
        {
            if(ans*base>=mod) return -1;
            else ans=ans*base;
        }
        if(base*base>=mod) return -1;
        else base=base*base;
        b>>=1;
    }
    if(ans>=mod) return -1;
    else return ans;
}
void zhixing(long long x)//在后缀表达式树中加入节点
{
    long long a=stack_num[top1];
    long long b=stack_num[top1-1];
    stack_num[top1]=0;
    top1--;
    stack_num[top1]=(++dian);
    tr[dian]=ss[x][1];
    ls[dian]=b,rs[dian]=a;
}
long long fi(long long xx)//计算欧拉函数
{
    long long x=xx,ans=xx;
    for(long long i=2; i*i<=xx; i++)
    {
        bool flag=0;
        while(x%i==0) x=x/i,flag=1;
        if(flag==1) ans=ans*(i-1)/i;
    }
    if(x>1) ans=ans*(x-1)/x;
    return ans;
}
long long gcd(long long a,long long b)
{
    if(a==0) return b;
    if(b==0) return a;
    while(a%b!=0)
    {
        long long t=a%b;
        a=b,b=t;
    }
    return b;
}
long long ccktr(node x)//高精度判断是否超出了mod来预处理数组q
{
    long long ans=0;
    for(long long i=1; i<=x.len; i++)
    {
        ans=ans*10+x.a[i];
        if(ans>=mod) return -1;
    }
    if(ans>=mod) return -1;
    return ans;
}
long long dgg(long long x)//提前预处理数组q判断b是否超出限制
{
    if(tr[x].len>=0)
    {
        long long u=ccktr(tr[x]);
        return q[x]=u;
    }
    else if(tr[x].len==-1)
    {
        long long a=dgg(ls[x]);
        long long b=dgg(rs[x]);
        if(a==-1||b==-1||a+b>=mod)
            q[x]=-1;
        else q[x]=a+b;
        return q[x];
    }
    else if(tr[x].len==-2)
    {
        long long a=dgg(ls[x]);
        long long b=dgg(rs[x]);
        if(a==-1||b==-1||a*b>=mod)
            q[x]=-1;
        else q[x]=a*b;
        return q[x];
    }
    else if(tr[x].len==-3)
    {
        long long a=dgg(ls[x]);
        long long b=dgg(rs[x]);
        if(a==-1||b==-1) q[x]=-1;
        else
        {
            long long c=check_power(a,b);
            if(c==-1) q[x]=-1;
            else q[x]=c;
        }
        return q[x];
    }
    else return -1;
}
long long jstr(node x,long long Mod)//计算高精度数模mod的值
{
    long long ans=0;
    for(long long i=1; i<=x.len; i++)
        ans=(ans*10%Mod+x.a[i])%Mod;
    return ans;
}
long long dg(long long x,long long Mod)
{
    if(tr[x].len>=0) return jstr(tr[x],Mod);//把高精度数字模低精度传回
    else if(tr[x].len==-1) return (dg(ls[x],Mod)+dg(rs[x],Mod))%Mod;
    else if(tr[x].len==-2) return (dg(ls[x],Mod)*dg(rs[x],Mod))%Mod;
    else if(tr[x].len==-3)
    {
        long long a=dg(ls[x],Mod);
        long long tun=fi(Mod);
        if(gcd(a,Mod)==1)//如果互质就直接下传phi(mod)成为b子树的mod数
        {
            long long b=dg(rs[x],tun)%tun;
            return power(a,b,Mod)%Mod;
        }
        else
        {
            if(q[rs[x]]==-1||q[rs[x]]>=tun)//否则判断b与phi(mod)的大小
            {
                long long b=dg(rs[x],tun)%tun;//b更大
                return power(a,b+tun,Mod)%Mod;
            }
            else return power(a,q[rs[x]],Mod)%Mod;
        }
    }
    else return -1;
}
int main()
{
//	freopen("exmid.in","r",stdin);
//	freopen("exmid.out","w",stdout);
    scanf("%lld",&n);
    for(long long i=1; i<=n; i++)
    {
        char ch=getchar();
        while(ch!='0'&&ch!='1')
            ch=getchar();
        if(ch=='0') a[i]=0;
        else a[i]=1;
    }
    scanf("%s",(s+1));
    len=strlen(s+1);
    long long flag=0;
    node num;
    num.len=0;
    for(long long i=1; i<=len; i++)
    {
        if('0'<=s[i]&&s[i]<='9')
        {
            num.len++;
            num.a[num.len]=s[i]-'0';
        }
        else
        {
            if(s[i]=='.') flag=1,ss[++tot][0].len=0,ss[tot][1]=num;
            else if(s[i]=='+'||s[i]=='*'||s[i]=='^')
            {
                flag=0;
                long long ans=0;
                for(long long j=1; j<=num.len; j++)
                {
                    ans=ans*10+num.a[j];
                    if(ans>9) break;
                }
                if(ans>n||ans<1)//优先级错误
                {
                    printf("error");
                    return 0;
                }
                ss[++tot][0].len=ans;
                //+对应-1，*对应-2，^对应-3
                if(s[i]=='+') ss[tot][1].len=-1;
                else if(s[i]=='*') ss[tot][1].len=-2;
                else if(s[i]=='^') ss[tot][1].len=-3;
            }
            else if(s[i]=='(')
            {
                flag=0;
                bool pd=0;
                for(int j=1; j<=num.len; j++)
                    if(num.a[j]!=0)
                    {
                        pd=1;
                        break;
                    }
                //括号挨着数
                if(pd==1)
                {
                    printf("error");
                    return 0;
                }
                ss[++tot][0].len=0;
                //(对应-4
                ss[tot][1].len=-4;
            }
            else if(s[i]==')')
            {
                bool pd=0;
                for(int j=1; j<=num.len; j++)
                    if(num.a[j]!=0)
                    {
                        pd=1;
                        break;
                    }
                //括号挨着数或者左括号开始括号中没有数
                if(pd==1||flag==0)
                {
                    printf("error");
                    return 0;
                }
                //）对应-5
                ss[++tot][0].len=0;
                ss[tot][1].len=-5;
            }
            else
            {
                //字符不正确
                printf("error");
                return 0;
            }
            num.len=0;
        }
    }
    if(flag==0)
    {
        //左括号未匹配
        printf("error");
        return 0;
    }
    //建立后缀表达式树
    for(long long i=1; i<=tot; i++)
    {
        if(ss[i][1].len>=0)
        {
            stack_num[++top1]=(++dian);
            tr[dian]=ss[i][1];
            //数字在表达式树上建点
        }
        else if(ss[i][1].len==-1||ss[i][1].len==-2||ss[i][1].len==-3)
        {
            while(check(stack_fu[top2],i)==1&&top2>0)//前面高级的字符弹出
            {
                if(top1<2) //字符没有匹配到两个数字
                {
                    printf("error");
                    return 0;
                }
                zhixing(stack_fu[top2]);
                stack_fu[top2]=0;
                top2--;
            }
            stack_fu[++top2]=i;
        }
        else if(ss[i][1].len==-4)
        {
            stack_fu[++top2]=i;
            //左括号直接加入
        }
        else if(ss[i][1].len==-5)
        {
            //右括号一直弹到左括号
            while(ss[stack_fu[top2]][1].len!=-4&&top2>0)
            {
                if(top1<2)
                {
                    printf("error");
                    return 0;
                }
                zhixing(stack_fu[top2]);
                stack_fu[top2]=0;
                top2--;
            }
            if(top2==0)//没匹配到左括号
            {
                printf("error");
                return 0;
            }
            stack_fu[top2]=0;
            top2--;
        }
    }
    while(top2>0)//最后把所有都弹完
    {
        if(ss[stack_fu[top2]][1].len==-4
                ||top1<2)//有左括号没匹配到右括号或者字符没有匹配到两个数字
        {
            printf("error");
            return 0;
        }
        zhixing(stack_fu[top2]);
        stack_fu[top2]=0;
        top2--;
    }
    dgg(stack_num[top1]);//预处理q数组判断b与phi(p)的大小
    printf("%lld",dg(stack_num[top1],mod));
    return 0;
}

