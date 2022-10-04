#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long 
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

signed main(){__
	int t= 1,n;
    cin>>t;
    while(t--){
        cin>>n;
        int ans = 0;
        set<int> st;
        for(int i = 1;i<=100000;i++){
            if(i*i<=n)st.insert(i*i);
            if(i<=1200 && (i*i*i)<=n)st.insert(i*i*i);
        }
        cout<<st.size()<<endl;
    }
    return 0;
}  
