// Source: https://www.luogu.com.cn/article/dz6igx5b
#include<iostream>
using namespace std;
long long /*请输入文本*/ T,n;
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        if(n%2==1) 
            puts("0");
		else 
            cout<<n*(n/2-1)<<endl;
    }
    return 0;
}
