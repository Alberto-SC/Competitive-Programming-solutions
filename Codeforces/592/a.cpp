#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
int main(){__
    int t = 1,n,a,b,c,d,k;
    cin>>t;
    while(t--){
        cin>>a>>b>>c>>d>>k;
        int x = a/c;
        if(a%c)x++;
        int y = b/d;
        if(b%d)y++;
        if(x+y<=k)cout<<x<<" "<<y<<endl;
        else cout<<-1<<endl;
    }
    return 0;
}

