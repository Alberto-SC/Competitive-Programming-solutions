#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long 
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

signed main(){__
	int t= 1,n,m,k;
    cin>>t;
    while(t--){
        cin>>n>>m>>k;
        bool flag = false;
        if(k == (n-1)+((m-1)*n))flag = true;
        cout << "NO\0YES\0" + 3 * flag << endl;
    }
    return 0;
}  
