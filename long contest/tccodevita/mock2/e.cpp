#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,ai;
    cin>>n;
    char coma;
    vector<int> nums(n*2);
    for(int i = 0;i<n;i++){
        cin>>ai;
        if(i <n-1)
            cin>>coma;
        nums[i] = nums[i+n] = ai;
    }
    int mx = -1000;
    for(int i = 0;i<5;i++){
        int sum = 0;
        for(int j = 0;j<n/5;j++){
            sum += nums[(j*5)+i]+nums[(j*5)+i+4];
        }
        if(((n/5) *5)< n)
            if((n/5)+1+i<n)
                sum+=nums[((n/5)*5)+i];
        mx = max(mx,sum);
    }
    cout<<mx<<"\n";
    return 0;
}