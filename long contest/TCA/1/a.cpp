#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define endl "\n"
const int maxn = 1007;
vector<int> divs[1000007];
vector<vector<int>> bit2D;
int n,m,q;

int sum2D(int x,int y){
    int ret = 0;
    for(int i =x;i>=0;i = (i &(i+1))-1)
        for(int j = y;j>=0;j = (j&(j+1))-1)
            ret+= bit2D[i][j];
    return ret;
}
int sum2D(int x0,int y0,int x,int y){
    return sum2D(x,y)-sum2D(x,y0-1)-sum2D(x0-1,y)+sum2D(x0-1,y0-1);
}

void add2D(int x ,int y ,int delta){
    for(int i = x;i<n;i = i| (i+1))
        for(int j = y;j<m;j = j|(j+1))
            bit2D[i][j] +=delta;
}

bool check(int z,int x,int y){
    vector<int> divs;
    for(int j = 1;j*j<=z;j++){
        if(z%j == 0){
            divs.push_back(j);
        }
    }    
    // cout<<"HI "<<z<<endl;
    if(z == 1)return sum2D(x,y,x,y);
    if(z == 0)return true;
    int nx = x, ny = y;
    for(auto c:divs){
        int t = z/c;
        // cout<<"DIV "<<c<<endl;
        if(nx+(t-1)<n){
            for(int i = 0;i<c;i++){
                ny = y-i;
                if(ny <0)break;
                if(ny+(c-1)<m){
                    if(sum2D(nx,ny,nx+(t-1),ny+(c-1)) == z)return true;
                }
            }
        }
        ny = y;
        if(nx-(t-1)>=0){
            for(int i = 0;i<c;i++){
                ny = y-i;
                if(ny <0)break;
                if(ny+(c-1)<m){
                    if(sum2D(nx-(t-1),ny,nx,ny+(c-1)) == z)return true;
                }
            }
        }
        ny = y;
        if(ny+(c-1)<m){
            for(int i = 0;i<t;i++){
                nx = x-i;
                if(ny <0)break;
                if(ny+(c-1)<m){
                    if(sum2D(nx,ny,nx+(t-1),ny+(c-1)) == z)return true;
                }
            }
        }
        nx = x;
        if(nx-(c-1)>=0){
            for(int i = 0;i<c;i++){
                nx = x-i;
                if(nx <0)break;
                if(nx+(t-1)<n){
                    if(sum2D(nx,ny-(c-1),nx+(t-1),ny) == z)return true;
                }
            }
        }
        nx = x;
        if(t== c)continue;
        // cout<<"YEAH"<<endl;
        if(nx+(c-1)<n){
            // cout<<"HELLO "<<nx+(c-1)<<endl;
            for(int i = 0;i<t;i++){
                ny = y-i;
                // cout<<nx<<" "<<ny<<" "<<nx+(c-1)<<" "<<ny+(t-1)<<endl;
                if(ny <0)break;
                if(ny+(t-1)<m){
                    if(sum2D(nx,ny,nx+(c-1),ny+(t-1)) == z)return true;
                }
            }
        }
        // cout<<"PUTO SI LLEGAS AQUÏ"<<endl;
        ny = y;
        if(nx-(c-1)>=0){
            for(int i = 0;i<t;i++){
                ny = y-i;
                if(ny <0)break;
                if(ny+(t-1)<m){
                    if(sum2D(nx-(c-1),ny,nx,ny+(t-1)) == z)return true;
                }
            }
        }
        ny = y;
        if(ny+(t-1)<m){
            for(int i = 0;i<c;i++){
                nx = x-i;
                if(ny <0)break;
                if(ny+(t-1)<m){
                    if(sum2D(nx,ny,nx+(c-1),ny+(t-1)) == z)return true;
                }
            }
        }
        nx = x;
        if(nx-(t-1)>=0){
            for(int i = 0;i<t;i++){
                nx = x-i;
                if(nx <0)break;
                if(nx+(c-1)<n){
                    if(sum2D(nx,ny-(t-1),nx+(c-1),ny) == z)return true;
                }
            }
        }
    }
    return false;
}

int main(){
    int x,y;
    cin>>n>>m>>q;
    vector<int> b(n*m+4,0);
    for(int i = 1;i<=n;i++){
        for(int j =1;j<=m;j++){
            b[i*j]++;
        }  
    }
    vector<int> sz;
    sz.push_back(0);
    for(int i = 0;i<n*m;i++)if(b[i])sz.push_back(i);
    sort(sz.begin(),sz.end());
    bit2D.resize(maxn+7,vector<int> (maxn+7,0));
    vector<vector<int>> matriz(maxn+7,vector<int> (maxn+7,0));
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            cin>>matriz[i][j];
            add2D(i,j,matriz[i][j]);
        }
    }
    for(int i = 0;i<q;i++){
        int type;
        cin>>type;
        cin>>x>>y;
        x--,y--;
        if(type==1){
            int z = sum2D(x,y,x,y);
            if(z == 0)add2D(x,y,1);
            else add2D(x,y,-1);
            z = sum2D(x,y,x,y);
        }
        else {
            int l = 0,r = sz.size()-1;
            while(l<r){
                int m = (l+r+1)>>1;
                if(check(sz[m],x,y))
                    l = m;
                else r = m-1;
            }

            cout<<sz[l]<<endl;
        }  
    }
	return 0;
}