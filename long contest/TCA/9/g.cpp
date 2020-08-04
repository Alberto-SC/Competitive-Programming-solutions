#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);


int manacher(string s){
    int n = s.size();
    vector<vector<int>> p(2,vector<int>(n,0));
    for(int z=0,l=0,r=0;z<2;z++,l=0,r=0)
        for(int i=0;i<n;i++)
        {
            if(i<r) p[z][i]=min(r-i+!z,p[z][l+r-i+!z]);
            int L=i-p[z][i], R=i+p[z][i]-!z;
            // // cout<<L<<" "<<R<<" "<<(L-1>=0) <<" "<<(R+1<n)<<endl;
            while(L-1>=0 && R+1<n && s[L-1]==s[R+1]) p[z][i]++,L--,R++;
            if(R>r) l=L,r=R;
        }
    int ans = 0;
    for(int i = 0;i<n;i++){
        ans += p[0][i];
        ans+= (p[1][i]+1);
    }
    return ans;
}
const int maxn = 100000;
int main(){__
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<int> ans(n,0);
    int sz = 0;
    string t;
    for(int i = 0;i<n;i++){
        if(s[i] == '-'){
            t.pop_back();
            ans[i]= manacher(t);
        }
        else {
            t+=s[i];
            ans[i] = manacher(t);
        }
    }
    for(auto c:ans)cout<<c<<" ";
    cout<<endl;
    return 0;
}