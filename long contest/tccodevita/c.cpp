#include <bits/stdc++.h>
using namespace std;
vector<int> nums;
int findMin() { 
    int n = nums.size(),sum = 0;
    for (int i = 0; i < n; i++) 
        sum += nums[i];   
    bool dp[n+1][sum+1]; 
    for (int i = 0; i <= n; i++) 
        dp[i][0] = true; 
    for (int i = 1; i <= sum; i++) 
        dp[0][i] = false; 

    for (int i=1; i<=n; i++){ 
        for (int j=1; j<=sum; j++) { 
            dp[i][j] = dp[i-1][j];   
            if (nums[i-1] <= j) 
                dp[i][j] |= dp[i-1][j-nums[i-1]]; 
        } 
    }    



    int diff = INT_MAX; 
    for (int j=sum/2; j>=0; j--) { 
        if (dp[n][j] == true) { 
           return j;
        } 
    } 
} 
int main(){
    int ai;
    int sum = 0;
    while(cin>>ai){
        nums.push_back(ai);
        sum+=ai;
    }
    int sumOne = findMin();
    cout<<max(sum-sumOne,sumOne)<<"\n";
    return 0;
}