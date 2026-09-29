// Source: https://www.luogu.com.cn/article/bhogstda
#include<bits/stdc++.h>
using namespace std;
int day=1,l,sum;//l用来存储字符串长度，随时备用
bool dm[40][2];//dm[i][0]用来标记日期i，dm[i][1]用来标记月份i
string s[10];//分别存储5个小段字符串
void f1(int p,int h){//f1函数针对时、分、秒
	//p表示哪一段字符串，h表示范围
	if(s[p][0]=='*') day*=h;
	else{
		bool flag=0;
		l=s[p].size();
		sum=0;
		for(int i=0;i<l;i++){
			if(s[p][i]==',') sum++;
			if(s[p][i]=='-') flag=1;
		}
		if(!flag){//是“,”情况
			day=day*(sum+1);
			return ;
		}
		flag=0;
		int left=0,right=0;
		for(int i=0;i<l;i++){
			if(s[p][i]=='-') flag=1;
			else if(!flag) left=left*10+(s[p][i]-'0');
			else right=right*10+(s[p][i]-'0');
		}
		day=day*(right-left+1);
	}	
}
void f2(int p,int h){//f2函数针对月、日
	//p、h意义同f1函数
	if(s[p][0]=='*'){
		for(int i=1;i<=h;i++){
			dm[i][p-3]=1;
		}
	}
	else{
		bool flag=0;
		int n=0;
		l=s[p].size();
		for(int i=0;i<l;i++){
			if(s[p][i]=='-') flag=1;
			else if(s[p][i]!=',') n=n*10+(s[p][i]-'0');
			else{
				dm[n][p-3]=1;
				n=0;
			}
		}
		if(!flag){//是“,”情况
			dm[n][p-3]=1;//扫尾，别忘了
			return ;
		}
		int left=0,right=0;
		flag=0;
		for(int i=0;i<l;i++){
			if(s[p][i]=='-') flag=1;
			else if(!flag) left=left*10+(s[p][i]-'0');
			else right=right*10+(s[p][i]-'0');
		}
		for(int i=left;i<=right;i++){
			dm[i][p-3]=1;
		}
	}	
}
int main(){
	for(int i=0;i<5;i++){
		cin>>s[i];
	}//输入
	f1(0,60);
	f1(1,60);
	f1(2,24);
	for(int i=1;i<=31;i++){
		dm[i][0]=0;
		dm[i][1]=0;
	}//初始化
	f2(3,31);
	f2(4,12);
	//检索哪些月和日
	int k[40]={0,31,28,31,30,31,30,31,31,30,31,30,31},ans=0;
	for(int i=1;i<=12;i++){
		if(dm[i][1]){
			for(int j=1;j<=k[i];j++){
				if(dm[j][0]) ans+=day;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
