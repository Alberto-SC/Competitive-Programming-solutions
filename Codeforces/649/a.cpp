#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

int main(){__
    int t,n,x;
    cin>>t;
    while(t--){
        cin>>n>>x;
        vector<int> nums(n);
        for(auto &c:nums)cin>>c;
        int sum = 0;
        sum = accumulate(nums.begin(),nums.end(),0);
        if(sum%x!=0){cout<<n<<endl;continue;}
        int left = 0,rigth = n-1;
        int ans = n;
        while(sum%x ==0 &&left<n && rigth>=0 &&  rigth>left){
            if((sum-nums[left]) %x != 0){sum-=nums[left];ans--;}
            else if((sum-=nums[rigth])%x != 0){sum-=nums[rigth];ans--;} 
            else {
                sum-=nums[rigth];
                sum-=nums[left];
                left++;
                rigth--;
                ans-=2;
            }
        }
        if(rigth == left&& nums[left]%x == 0)ans--;
        if(ans==0)ans--;
        cout<<ans<<endl;
    }

    return 0;
}