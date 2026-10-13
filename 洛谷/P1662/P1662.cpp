// Source: https://www.luogu.com.cn/article/6rvm6n0l
#include<cstdio>
using namespace std;
int n,i,j,k,t,pd,m;
int ha(int x,int y,int z,int a)
//模拟函数，x代表区域端点，y代表n，z是当前在哪个人，a表示如何传递方向
{
    t=z;
    for(i=x;i<=y;i++)
    {
        t+=a;//a有两值，1和-1，这样就不用每次判定浪费时间
        if(i%7==0)
        a=-a;//是7的倍数就变方向
        else
        {
            k=i;
            while(k)//还有含有7的数也要变
            {
                if(k%10==7)
                {a=-a;break;}
                k/=10;
            }
        }
        if(t==0)t=1337;
        if(t==1338)t=1;//界限规定
    }
    printf("%d",t);//答案
}
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("seven.out","w",stdout);
    scanf("%d",&n);
    //下面是最暴力毒瘤的程序，20个if划分区域QWQ
    if(n<5e7){ha(1,n,0,1);}
    //分别对区域进行划分，跑5e7的模拟
    else if(n<1e8){ha(5e7,n,157,-1);}
    else if(n<1e8+5e7){ha(1e8,n,547,1);}
    else if(n<2e8){ha(1e8+5e7,n,346,-1);}
    else if(n<2e8+5e7){ha(2e8,n,867,-1);}
    else if(n<3e8){ha(2e8+5e7,n,892,1);}
    else if(n<3e8+5e7){ha(3e8,n,893,-1);}
    else if(n<4e8){ha(3e8+5e7,n,1212,-1);}
    else if(n<4e8+5e7){ha(4e8,n,63,1);}
    else if(n<5e8){ha(4e8+5e7,n,893,-1);}
    else if(n<5e8+5e7){ha(5e8,n,1302,-1);}
    else if(n<6e8){ha(5e8+5e7,n,1055,1);}
    else if(n<6e8+5e7){ha(6e8,n,98,-1);}
    else if(n<7e8){ha(6e8+5e7,n,957,1);}
    else if(n<7e8+5e7){ha(7e8,n,1279,-1);}
    else if(n<8e8){ha(7e8+5e7,n,1279,-1);}
    else if(n<8e8+5e7){ha(8e8,n,1279,-1);}
    else if(n<9e8){ha(8e8+5e7,n,143,1);}
    else if(n<9e8+5e7){ha(9e8,n,959,1);}
    else if(n<=1e9){ha(9e8+5e7,n,934,-1);}
    //说一下那个n<=1e9的等于，一开始我没写也对了，因为最大数据点好像不是1e9
    return 0;
}
