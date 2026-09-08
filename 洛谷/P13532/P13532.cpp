#include <iostream> // 不用万能头文件就得写这些头文件
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;
 
long long premax[500005]; // 预处理前缀最大值的数组
pair <long long, long long> a[500005];
// 礼物价值的数组，为了将 a[i] 和 b[i] 绑定，需要使用 pair
multiset <long long> s;
// 礼物价格的数值可以重复，使用可重集合 multiset
 
bool cmp(pair <long long, long long> a, pair <long long, long long> b)
// 自定义排序函数，注意从大到小排序
{
	return a.first > b.first;
}
 
int main()
{
	long long n;
    scanf("%lld", &n); // 输入，本题卡常，要用 scanf
    s.clear();// 清空集合
    //本题不需要，但要养成好习惯，防止多测不清空，爆零两行泪
    for (long long i = 1; i <= n; ++i) 
    {
        scanf("%lld %lld", &a[i].first, &a[i].second);
        // 输入礼物价值
        s.insert(a[i].second); // 装入可重集合
    }
    sort(a + 1, a + n + 1, cmp); // 排序
    premax[0] = -2e18; // 初始化前缀最大值数组的首项为极小值
    for (long long i = 1; i <= n; ++i)
    // 计算 b[i] 的前缀最小值，注意是 second 不是 first
    {
        premax[i] = max(premax[i - 1], a[i].second);
    }
    long long minn = 2e18; // 初始化答案变量为极大值
    for (long long i = 1; i <= n; ++i)
    // 遍历数组并假设 a[i] 为 a 中选中的最大值
    {
       auto it = s.lower_bound(a[i].second);
      // a[i] 选过了，选不了 b[i] 了，删除这一项
       s.erase(it);
      // 注意要删除迭代器，如果删除数值会删除所有等于 b[i] 的元素
        if (i > 1) // 判断一下，以防越界
        {
            minn = min(minn, abs(premax[i - 1] - a[i].first));
          // 更新答案变量
        }
        if (premax[i - 1] <= a[i].first)
        // 如果目前 a 中选中的礼物价值的最大值比 b 大 
        {
            minn = min(minn, abs(premax[i - 1] - a[i].first));
            auto it1 = s.lower_bound(a[i].first), it2 = s.upper_bound(a[i].first);
            // 在 multiset 中选择最接近 a[i] 的数
            // 注意 lower 和 upper 不要写错
            if (it2 != s.begin()) // 判断一下，以防越界
            {
                it2--;
                // it2 指向前一个元素，也就是最后一个小于等于 a[i] 的元素
                if (it1 != s.end()) // 再判断一下，以防越界
                {
                    minn = min(minn, abs(*it1 - a[i].first)); // 更新答案变量
                }
                if (it2 != s.end()) // 同上
                {
                    minn = min(minn, abs(*it2 - a[i].first));
                }
            }
            else
            // 如果 a[i] 比 multiset 中所有元素都小，说明不存在最后一个小于等于 a[i] 的元素
            {
                if (it1 != s.end()) // 只更新 it1 的答案
                {
                    minn = min(minn, abs(*it1 - a[i].first));
                }
            }
        }
        s.insert(a[i].second);
        // 在 multiset 中重新加入 b[i]
    }
    printf("%lld", minn); // 输出答案
	
	return 0; 
}
