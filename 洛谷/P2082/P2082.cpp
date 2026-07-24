#include <bits/stdc++.h>
using namespace std;
struct p1047//没错，一开始只是想写一个校门外的树plus
{
    long long num;
    bool t;//0表示这是一个左括号，1表示右括号
}p,a[200005];
bool cmp(p1047 x,p1047 y)
{
    if(x.num==y.num)
        return x.t<y.t;
    return x.num<y.num;
}
int main()
{
    int m,x;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld",&a[i*2-1].num,&a[i*2].num);
        //每个区间由一个左括号和一个右括号组成
        a[i*2-1].t=0;
        a[i*2].t=1;
    }
    sort(a+1,a+m*2+1,cmp);//对所有括号排序
    long long st=a[1].num;//第一个左括号
    int cs=1;//剩余括号数量
    long long tot=0;//总长度
    for(int i=2;i<=m*2;i++)
    {
        if(a[i].t==0)//左括号
            cs++;
        else//右括号
            cs--;
        if(cs==0)//一段区间结束，结算
        {
            tot+=a[i].num-st+1;
            st=a[i+1].num;
            //加入下一个左括号
        }
    }
    cout<<tot;
    return 0;
}
