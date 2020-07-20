#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for(auto &x:nums)cin>>x;
    for(int i = 0;i<n;i++){
        int first = nums[i]%10;
        int second = (nums[i]/10)%10;
        int third = (nums[i]/100)%10;
        int mx = max(first,max(second,third));
        int mn = min(first,min(second,third));
        mx*=11;
        mn*=7;
        int newnum = mx+mn;
        if(newnum >=100)
            newnum = newnum%10+((newnum/10)%10)*10;
        nums[i] = newnum;
    }
    vector<int> bucket(10,4);
    int ans = 0;
    for(int i = 0;i<n;i++){
        for(int j = i+2;j<n;j+=2){
            if((nums[i]/10)%10 == (nums[j]/10)%10 && bucket[(nums[i]/10)%10]>0 && bucket[(nums[j]/10)%10]>0){
                bucket[(nums[i]/10)%10]--;
                bucket[(nums[j]/10)%10]--;
                ans++;
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}