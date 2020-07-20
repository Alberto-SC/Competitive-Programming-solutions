#include<bits/stdc++.h>
using namespace std;
int maint(){
    int n;
    vector<int> nums(n);
    for(int i =0;i<n;i++){
        cin>>nums[i];
    }
    long long min = nums[0],max=nums[0];
    for(int i = 0;i<n;i++){
        cout<<min+max<<endl;
        if(nums[i]>max)max =nums[i];
        if(nums[i]<min)min =nums[i];
    }
    return 0;
}