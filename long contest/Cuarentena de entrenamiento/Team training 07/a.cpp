#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
unordered_map<char,int> mp;
int n;
vector<string> s;
int cont = 0;
lli solve(vector<lli> A, lli l,lli mask){
    // cout<<l<<" "<<mask<<endl;
    if(l == mp.size()){
        // for(auto c:A)cout<<c<<" "; 
        // cout<<endl;
        vector<lli> nums(n);
        for(lli i = 0;i<n;i++){
            lli z = 0;
            lli cont = 0;
            lli y = 1;
            for(lli j = s[i].size()-1;j>=0;j--){
                z+= A[mp[s[i][j]]]*y;
                cont++;
                if(j == 0 && A[mp[s[i][j]]] == 0)return 0;
                y*=10;
            }
            nums[i] = z;
        }
        lli sum = 0;
        for(lli i = 0;i<n-1;i++){
            sum+=nums[i];
        }
        if(sum == nums[n-1]){
            // for(auto c:mp){
                // cout<<"("<<c.first<<","<<A[c.second]<<")";
            // }
            // cout<<endl;
            // for(int i = 0;i<n;i++)cout<<nums[i]<<" ";
            // cout<<endl;
            return 1;
        }
        else
            return 0;    
    }
    lli x = 0;
    for(lli i = 0;i<=9;i++){
        if(i == 0 && l<cont)continue;
        if((mask>>i) &1)continue;
        A[l] = i;
        lli aux = mask;
        aux |= 1<<i;
        x+=solve(A,l+1,aux);
    }
    return x;
}

int main(){
    while(cin>>n){
        s.resize(n);
        for(auto &c:s)cin>>c;
        int key = 0;
        mp.clear();
        cont = 0;
        for(int i = 0;i<n;i++){
            if(!mp.count(s[i][0]))mp[s[i][0]] = key++,cont++;
        }
        for(int i = 0;i<n;i++){
            for(int j = 1;j<s[i].size();j++){
                if(!mp.count(s[i][j]))mp[s[i][j]] = key++;
            }
        }
        // for(auto c:mp){
            // cout<<c.first<<" "<<c.second<<endl;
        // }
        int mask = 0;
        vector<lli> A(mp.size());
        cout<<solve(A,0,mask)<<endl;
    }
    return 0;
}