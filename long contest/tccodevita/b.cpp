#include <bits/stdc++.h>
using namespace std;
typedef long long int;
int main(){
    int n;
    cin>>n;
    vector<lli> nums(n);
    for(auto &x:nums)cin>>x;
    sort(nums.begin(),nums.end());
    vector<int> flags(n,0);
    lli actual;
    for(int i = 1;i<=n;i++){
        int aux = 0;
        lli actual;
        while(flags[aux] != 0 && aux<n){aux++;}
        actual = nums[aux];
        flags[aux] = i;
        if(aux == n-1)break;
        for(int j =aux;j<n;j++){
            if(nums[j]>actual&& flags[j] == 0){
                actual = nums[j];
                flags[j] = i;
            }
        }
    }
    unorder_set<int> total;
    for(int i = 0;i<n;i++)
        total.emplace(flags[i]);
    cout<<total.size()<<"\n";
    return 0;
}