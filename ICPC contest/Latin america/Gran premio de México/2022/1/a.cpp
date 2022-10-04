#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long 
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

struct Basis {
    vector<int> a;
    bool insert(int x) {
        for (auto &i: a) x = min(x, x ^ i);
        if (!x) return false;
        for (auto &i: a) if ((i ^ x) < i) i ^= x;
        a.push_back(x);
        sort(a.begin(), a.end());
        return true;
    }
    bool can(int x) {
        for (auto &i: a) x = min(x, x ^ i);
        return !x;
    }
    int maxxor(int x = 0) {
        for (auto &i: a) x = max(x, x ^ i);
        return x;
    } 
    int minxor(int x = 0) {
        for (auto &i: a) x = min(x, x ^ i);
        return x;
    }
    int kth(int k) { // 1st is 0
        int sz = (int)a.size();
        if (k > (1LL << sz)) return -1;
        k--; int ans = 0;
        for (int i = 0; i < sz; i++) if (k >> i & 1) ans ^= a[i];
        return ans;
    }
}t;

signed main(){__	
    int n;
    cin>>n;
    vector<int> nums(n);
    for(auto &c:nums)cin>>c;
    int x = 0;
    Basis bs;
    for(int i = 0;i<n;i++){
      if(!bs.insert(nums[i]))
        x^=nums[i];
    }
    int y = bs.maxxor();
    cout<<y<<endl;
    cout<<x+y<<endl;
    return 0;
} 
