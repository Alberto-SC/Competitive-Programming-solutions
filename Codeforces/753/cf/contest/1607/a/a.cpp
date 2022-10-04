#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long 
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

signed main(){__
	int t= 1,n;
    cin>>t;
    while(t--){
        string order;
        cin>>order;
        string s;
        vector<int>pos(26);
        for(int i = 0;i<order.size();i++){
            pos[order[i]-'a'] =i;
        }
        cin>>s;
        n = s.size();
        int ans  = 0;

        for(int i = 1;i<n;i++){
            ans+=abs(pos[s[i]-'a']-pos[s[i-1]-'a']);
        }
        cout<<ans<<endl;
    }
    return 0;
}  
