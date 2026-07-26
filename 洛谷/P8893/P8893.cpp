#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset> 
#include <queue>
#define maxn 5003
using namespace std;

vector<int> Edge[maxn];
bitset<maxn> Avai;
int N,K,p;
int R;
int In[maxn];

int First,End,Num;

queue<pair<int,int> > Q;

int main()
{
	while(!Q.empty())
		Q.pop();
	scanf("%d%d%d",&N,&K,&p);
	for(int i = 1 ; i<= p ; i++)
	{
		scanf("%d",&Num);
		Avai[Num] = true;
		Q.push({Num,0});
	}
	scanf("%d",&R);
	for(int i = 1 ; i<= R ; i++)
	{
		scanf("%d%d",&End,&Num);
		while(Num--)
		{
			scanf("%d",&First);
			Edge[First].push_back(End);
			In[End]++;
		}
	}
	while(!Q.empty())
	{
		pair<int,int> u = Q.front();
		Q.pop();
		int ID = u.first;
		int Day = u.second;
		if(!Avai[ID])
			continue;
		if(ID == K)
		{
			printf("%d\n",Day);
			return 0;
		}
		for(int End: Edge[ID] )
		{
			In[End]--;
			if(In[End] == 0)
			{
				Avai[End] = true;
				Q.push({End,Day+1});
			}
		}
	}
	puts("-1");
	return 0;
}
