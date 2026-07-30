#include <iostream>
#include <map>
#include <set>
#define IL inline
using namespace std;
const int N = 1e5 + 10;

struct node
{
    long double k, b;
}a[N];

int main()
{
    int n;
    cin >> n;
    int m = 0;
    set<pair<long double, long double> > p;
    for(int i = 1;i <= n;i++)
    {
        long double x, y;
        cin >> x >> y; 
        p.insert({x, y});//set 去重。 
    }
    for(auto i = p.begin();i != p.end();i++) //遍历并存入结构体数组。 
    {
        a[++m] = {(*i).first, (*i).second};
    }
    int ans = 0;
	
    for(int i = 1;i <= m;i++)
    {
		set <pair<long double,long double> > o;
        for(int j = 1;j < i;j++)
        {
            long double k1 = a[i].k;
            long double k2 = a[j].k;
            long double b1 = a[i].b;
            long double b2 = a[j].b;
            if(k1 == k2) continue; //斜率一致，平行，过掉。 
            long double x1 = (b2 - b1)  / (k1 - k2);
            long double y1 = k1 * x1 + b1;
            //根据公式计算交点。
            o.insert({x1, y1});
            //加入 set 去重。
        }
        ans += (o.size() + 1);
    }
    cout << ans + 1 << endl; //初始有一部分，要加一。
    return 0;
}
