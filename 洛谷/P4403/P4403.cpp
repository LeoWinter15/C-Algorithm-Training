#include <cstdio>
#include <cstring>
long long x[1000001],y[1000001],z[1000001];
long long n=0,l=0,r=0;
long long min(long long x,long long y)
{
    return x<y?x:y;
}
long long max(long long x,long long y)
{
    return x>y?x:y;
}
long long calc(long long d)
{
    long long da=0;
    for(long long i=1;i<=n;i++)
    {
        if(x[i]<=d)
        {
            da+=(min(d,y[i])-x[i])/z[i]+1;
        }
    }
    return da;
}
int main()
{
    long long t=0;
    scanf("%lld",&t);
    while(t--)
    {
        long long ans=0;
        l=0,r=0,n=0;
        scanf("%lld",&n);
        for(long long i=1;i<=n;i++)
        {
            scanf("%lld %lld %lld",&x[i],&y[i],&z[i]);
            r=max(r,y[i]);
        }
        if(calc(r)%2==0)
        {
            printf("Poor QIN Teng:(\n");
            continue;
        }
        while(l<r)
        {
            long long mid=(l+r)/2;
            if(calc(mid)%2==1)
            {
                r=mid;
            }
            else
            {
                l=mid+1;
            }
        }
        for(long long i=1;i<=n;i++)
        {
            if(x[i]>l || y[i]<l)
            {
                continue;
            }
            if((l-x[i])%z[i]==0)
            {
                ans++;
            }
        }
        printf("%lld %lld\n",l,ans);
    }
    return 0;
}

