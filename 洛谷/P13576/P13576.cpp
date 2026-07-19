#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	for(;T--;)
	{
		int a[11];// 卡片个数 
		memset(a,0,sizeof(a));
		for(int i = 1;i <= 9;i++)
			cin >> a[i];
		//将 1 和 2 变成 3
		if(a[1] <= a[2])
			a[3] += a[1],a[2] -= a[1],a[1] = 0;
		else if(a[1] > a[2])
			a[1] -= a[2],a[3] += a[2],a[2] = 0;
		//如果 1 还有剩余，将 1 变成 2 和 3
		if(a[1] != 0)
		{
			// 特判 a[1] 只剩一个 
			if(a[1] == 1)
			{
				for(int i = 3;i <= 9;i++)
				{
					if(a[i])
					{
						a[i] -= 1,a[i + 1] += 1;
						a[1] = 0;
						break;
					}
				}
			}
			else if(a[1] % 3 == 0) // 111111 - > 3 + 3
			{
				a[3] += a[1] / 3,a[1] = 0;
			}
			else if(a[1] % 3 == 1) // 1111111 - > 4 + 3
			{
				a[1] -= 4,a[4] += 1;
				a[3] += a[1] / 3,a[1] = 0;
			}
			else                   // 11111 - > 2 + 3
			{
				a[1] -= 2,a[2] += 1;
				a[3] += a[1] / 3,a[1] = 0;
			}
		} 
		//答案 
		long long ans = 1;//记得开 long long 
		for(int j = 2;j <= 10;j++)
		{
			for(int i = 1;i <= a[j];i++)
			{
				ans = ans * j % 998244353;
			}
		}
		cout << ans << "\n";
	} 
	return 0;
} 
