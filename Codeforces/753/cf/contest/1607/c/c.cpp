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
        for(auto &c:nums)cin>>c;
        int s = 0;
        priority_queue<int,vector<int>,greater<int>> pq;
        int next;
        for(int i = 0;i<n;i++)
            pq.push(nums[i]);
        int last = pq.top();
        while(pq.size()>1){
            next = pq.top();
            if(next+s<last)break;
            else s+=abs(next+s);
            pq.pop();
            last = next;
        }
        next = pq.top();
        cout<<next+s<<endl;
    }
    return 0;
}  
