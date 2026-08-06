#include<bits/stdc++.h>
using namespace std;
int n,sum,a[25001];
int main(){
    while(cin>>n&&n){
        if(!a[n]){
            sum=0;
            for(int i=1,j=n;i<=n;i++){
				j=n;
                while(i*i+j*j>n*n) sum++,j--;
            }
            a[n]=(n*2+1)*(n*2+1)-4*sum;
            cout<<(n*2+1)*(n*2+1)-4*sum<<endl;
        }
        else cout<<a[n]<<endl;
    }
}
