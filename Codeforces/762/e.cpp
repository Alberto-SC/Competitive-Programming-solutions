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
        vector<int> nums(n);
        vector<int> f(n+1);
        for(auto &c:nums)cin>>c;
        for(int i = 0;i<n;i++)
            f[nums[i]]++;
        
        vector<int> ac(n+1);
        ac[0]= f[0];
        for(int i = 1;i<=n;i++)
            ac[i] = ac[i-1] +f[i];

        int first = -1;
        if(!f[0]){
            for(int i = 0;i<=n;i++)
                cout<<-1<<" ";
            cout<<endl;
            continue;
        }
        for(int i = 1;i<=n;i++){
            if(ac[i-1]<i || (ac[i-1]==i && !f[i])){
                first =i;
                break;
            }
        }
        int last = first-1;
        int cont = 0;

        for(int i = first-1;i>=0;i--){
            if(f[last])continue;
            while(f[last]<=1){
                last--;
            }
            cont+=i-last;
            f[last]--;

            
        }   
        cout<<cont<<endl;
        cout<<first<<endl;

        // for(int i = 1;i<=n;i++){
        //     if(x[i-1]!=-1)cout<<f[i]+x[i-1]<<" ";
        //     else cout<<-1<<" ";
        //     if(f[i]){
        //         x[i] = x[i-1];
        //     }
        //     else{
        //         if(last.size()){
        //             int idx = *(--last.end());
        //             f[idx]--;
        //             if(f[idx]==1)
        //                 last.erase(idx);
        //             x[i] = x[i-1] + (i-idx);
        //             if(f[i]-1)last.insert(idx);
        //         }
        //         else{
        //             x[i] = -1;
        //         }
        //     }
        // }
        // cout<<endl;     
        // for(int i = 0;i<=n;i++){
        //     cout<<x[i]<<" ";
        // }
        // cout<<endl;
    }
    return 0;
}  

// 0 1 4 6 6 6 6 8 