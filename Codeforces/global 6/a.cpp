#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<string> nums(n);
    for(int i = 0;i<n;i++){
        cin>>nums[i];
    }
    for(int i = 0;i<n;i++){
        bool flag = true;
        int sum = 0;
        for(int j = 0;j<nums[i].size();j++){
            if(nums[i][j]%2 == 0)flag = true;
            sum += nums[i][j]-'0';
        }
        cout<<sum<<endl;
        if(flag && sum%3 == 0)
            cout<<"red"<<endl;
        else cout<<"cyan"<<endl;
    }
    return 0;
}