#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long 
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

signed main(){__
	int t= 1,n,x;
    cin>>t;
    while(t--){
        cin>>x>>n;
        if(n==0)cout<<x<<endl;
        else if(x%2==0){
            if(n%4==0)cout<<x+0<<endl;
            else if(n%4==1)cout<<x-n<<endl;
            else if(n%4==2)cout<<x+1<<endl;
            else cout<<x+(4*((n/4)+1))<<endl;
        }
        else {
            if(n%4==0)cout<<x+0<<endl;
            else if(n%4==1)cout<<x+n<<endl;
            else if(n%4==2)cout<<x-1<<endl;
            else cout<<x-(4*((n/4)+1))<<endl;
        }
    }
    return 0;
}
//1  2  3 4  5   6   7  8   9  10  11  12   13
//1 -1 -4 0  5  -1  -8  0  -7   3  14   2  -11
