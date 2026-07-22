#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int n,cnt=0,ans,temp=0;
struct node
{
    int x;
    int y;
}a[100003],b[100003]; 
bool rule(const node &s1,const node &s2)
{
    if(s1.x==s2.x) return s1.y<s2.y;
//这里把同色的排在一起，方便后续操作 
    else return s1.x<s2.x;
} 
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x>>a[i].y;
    }
    sort(a+1,a+n+1,rule);
    for(int i=1;i<=n;i++)
    {
        if(a[i-1].x!=a[i].x||a[i-1].y!=a[i].y)
        {
            b[++cnt]=a[i];
        } 
        //这里我们通过if语句来筛去同色牌中数值相同的牌 
    }
    for(int i=1;i<=cnt;i++)//枚举区间右端点 
    {
        temp=0;
        //注意此处一定要写在第一个循环和第二个循环之间 
        for(int j=i;j>=1;j--)//枚举区间左端点 
        {
            if(b[i].x==b[j].x&&b[i].y-b[j].y+1<=n)
            //如果是同色牌并且张数差小于等于n则一定能够通过换牌实现同花顺 
            {
                temp++; 
            }
            else break;//不符合条件则退出 
        }
        if(temp>ans) ans=temp;//取所有可行方案中最大值 
    }
    cout<<n-ans<<endl; 
    return 0;
}