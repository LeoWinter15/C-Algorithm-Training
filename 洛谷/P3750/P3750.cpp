// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 100010
#define mod 100003
using namespace std;
typedef long long ll;
ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,k;
int a[maxn];
int cnt=0;
ll f[maxn];
ll quick_pow(ll x,ll p)
{
    ll an=1;
    ll po=x;
    while(p)
    {
        if(p%2)  an=(an*po)%mod;
        po=(po*po)%mod;
        p/=2;   
    }
    return an;
}
int main()
{
    n=read();k=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=n;i>=1;i--)
    {
        if(a[i])
        {
            cnt++;
            for(int j=1;j*j<=i;j++)
            {
                if(i%j==0)
                {
                    a[j]^=1;
                    if(j*j!=i)  a[i/j]^=1;
                }
            }
        }
    }
    f[n+1]=0;
    for(int i=n;i>=1;i--)
    {
        ll tmp=(ll)(n-i)*f[i+1]%mod;
        tmp=(tmp+(ll)n)%mod;
        tmp=tmp*quick_pow(i,mod-2)%mod;
        f[i]=tmp;
    }
    ll tmp=0;
    if(cnt<=k)   tmp=cnt;
    else{
        for(int i=cnt;i>k;i--)  tmp=(tmp+f[i])%mod;
        tmp=(tmp+k)%mod;
    }
    for(int i=1;i<=n;i++)  tmp=(tmp*(ll)i)%mod;
    printf("%lld\n",tmp);
    return 0;
}
