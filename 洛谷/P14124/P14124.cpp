// Source: https://www.luogu.com.cn/article/d34xl47q
#include<bits/stdc++.h>
using namespace std;
int T;
string s;
void solve (){
    cin>>s;
    if (s=="ikimasu"){  //特判
        cout<<"itte\n";
        return ;
    }
    int p=s.size()-6;  //存变化下标
    if (s[p]=='h'){
        p--;
    }
    string te="";
    switch (s[p]){
        case 'c':
        case 'r': te="tte";   break;
        case 'm':
        case 'b':
        case 'n': te="nde";   break;
        case 'k': te="ite";   break;
        case 'g': te="ide";   break;
        case 's': te="shite"; break;
    }
    for (int i=0; i<p; i++){
        cout<<s[i];
    }
    cout<<te<<"\n";
}
int main(){
    cin>>T;
    while (T--){
        solve ();
    }
    return 0;
}
