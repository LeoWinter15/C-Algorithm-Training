// Source: https://www.luogu.com.cn/article/khr95drc
#include<bits/stdc++.h>
using namespace std;
int T,n,m,r[1010][1010],c[1010][1010],ans;
char a[1010][1010],A[1010][1010];
pair<int,int>f[1010][1010];
pair<int,int>find(int x,int y){
    if(f[x][y]==make_pair(x,y))return{x,y};
    pair<int,int>fa=find(f[x][y].first,f[x][y].second);
    return f[x][y]=fa;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    for(int t=1;t<=T;t++){
        cout<<"Case #"<<t<<": ";
        cin>>n>>m;
        ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
                A[i][j]=a[i][j];
                f[i][j]={i,j};
            }
        }
        for(int i=1;i<=n;i++){
            r[i][0]=0;
            for(int j=1;j<=m;j++){
                r[i][j]=r[i][j-1]+1;
                if(a[i][j]=='#'){
                    r[i][j]=0;
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=m;j>0;j--){
                if(a[i][j]=='#'){
                    continue;
                }
                for(int L=j-r[i][j]+1,R=j;L<R;L++,R--){
                    pair<int,int>X=find(i,L),Y=find(i,R);
                    if(X==Y)continue;
                    f[X.first][X.second]=Y;
                }
                j-=r[i][j];
            }
        }
        for(int j=1;j<=m;j++){
            c[0][j]=0;
            for(int i=1;i<=n;i++){
                c[i][j]=c[i-1][j]+1;
                if(a[i][j]=='#'){
                    c[i][j]=0;
                }
            }
        }
        for(int j=1;j<=m;j++){
            for(int i=n;i>0;i--){
                if(a[i][j]=='#'){
                    continue;
                }
                for(int L=i-c[i][j]+1,R=i;L<R;L++,R--){
                    pair<int,int>X=find(L,j),Y=find(R,j);
                    if(X==Y)continue;
                    f[X.first][X.second]=Y;
                }
                i-=c[i][j];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]=='#'||a[i][j]=='.'){
                    continue;
                }
                pair<int,int>X=find(i,j);
                a[X.first][X.second]=a[i][j];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]=='#'||a[i][j]!='.'){
                    continue;
                }
                pair<int,int>X=find(i,j);
                a[i][j]=a[X.first][X.second];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]!=A[i][j]){
                    ans++;
                }
            }
        }
        cout<<ans<<'\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cout<<a[i][j];
            }
            cout<<'\n';
        }
    }
}
