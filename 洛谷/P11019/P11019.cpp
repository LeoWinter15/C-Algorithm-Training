// Source: https://www.luogu.com.cn/article/zvx0pdm4
#include<bits/stdc++.h>
using namespace std;
const int N=105;
char a[N],b[N];
int main(){
	scanf("%s",a+1); //小trick，这样读入的字符串下标从1开始
	int l=strlen(a+1); 
	cout<<"/";
	for(int i=1;i<=l;i++){
		if(a[i]==']') break;
		if('A'<=a[i]&&a[i]<='Z'){
			cout<<(char)(a[i]-'A'+'a'); //将大写转成小写输出
		}
	}
	return 0;
}
