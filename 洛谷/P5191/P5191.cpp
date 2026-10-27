// Source: https://www.luogu.com.cn/article/pmfntir1
#include <bits/stdc++.h>
using namespace std;
const int N{1000};
list<int> e[N+5];int ind[N+5];
bitset<N+5> s[N+5];
int d,m,n;
void TP()
{
    queue<int> q;
    for (int i{1};i<=d;++i)
        if (ind[i]==0) q.push(i),s[i][i]=1;
    while (q.size())
    {
        int u{q.front()};q.pop();
        for (auto v:e[u])
        {
            --ind[v];
            s[v]|=s[u];
            if (ind[v]==0) q.push(v);
        }
    }
}
int qp;
int pp[MAXN];
vector<int> ans;
int main()
{
    cin>>d>>m>>n;
    for (int i{1};i<=m;++i)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        e[a].push_back(b);++ind[b];
    }
    TP();
    queue<int> q;
    for (int i{1};i<=n;++i)
        scanf("%d",&qp),pp[qp]=true,q.push(qp);
    while (q.size())
    {
        int u{q.front()};q.pop();
        ans.push_back(u);
        for (int j{1};j<=d;++j)
        {
            if (pp[j]!=0) continue;
            if ((s[j]&s[u])==s[u])
            {
                pp[j]=true;
                q.push(j);
            }
        }
        pp[u]=-1;
    }
    sort(ans.begin(),ans.end());
    for (auto x:ans) cout<<x<<" ";
    return 0;
}
