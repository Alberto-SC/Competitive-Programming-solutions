#include <bits/stdc++.h>
using namespace std;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
const int maxn = 100007;
vector<int> bit(maxn,0);
int sum(int idx) {
    int ret = 0;
    for (++idx; idx > 0; idx -= idx & -idx)ret += bit[idx];
    return ret;
}

int sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

void add(int idx, int val) {
    for (++idx; idx < maxn-1; idx += idx & -idx) bit[idx] += val;
}


bool lucky(int n){
    while(n){
        if( n%10 -4 && n%10 -7)return 0;
        n/=10;
    }
    return 1;
}
int main(){__
    int n,m,l,r,d;
    cin>>n>>m;
    vector<int> nums(n);
    vector<int> a(maxn,0);
    for(int i = 0;i<10007;i++)
        a[i] = lucky(i);
    
    for(auto &x:nums)cin>>x;
    for(int i = 0;i<n;i++)if(a[nums[i]])add(i,1);
    string s;
    for(int i = 0;i<m;i++){
        cin>>s;
        if(s[0]== 'c'){
            cin>>l>>r;
            l--,r--;
            cout<<sum(l,r)<<endl;
        }
        else {
            cin>>l>>r>>d;
            l--,r--;
            for(int j = l;j<=r;j++){
                if(a[nums[j]])add(j,-1);
                nums[j]+=d;
                if(a[nums[j]])add(j,1);
            }
        }
    }

    return 0;
}