#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long int lli;
const int m = 1e9 + 9;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

lli mod_pow(lli a,lli b){
    lli x = 1;
    while(b){
        if(b&1)x = (x*a)%m;
        a = (a*a)%m;
        b>>=1;        
    }
    return x;
}

vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) { 
        long long cur_h = (h[i+S] + m - h[i]) % m; 
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}

vector<string> t;
vector<vector<lli>> hash_b;
int r,c,a,b;
lli get_hash(int j,int l){
    cout<<j<<" "<<l<<endl;
    lli x = hash_b[j][l+c-1];
    lli y = mod_pow(hash_b[j][l],m-2);
    return (x*y)%m;
}


int main(){__
    while(cin>>r>>c>>a>>b){
        vector<string> s(r);
        t.resize(a);
        for(int i = 0;i<r;i++)
            cin>>s[i];
        for(int i = 0;i<a;i++)
            cin>>t[i];


        int cont = 0;
        for(int j = 0;j<a;j++){
            // cout<<"J: "<<j<<endl;
            vector<int> ocurrences; 
            ocurrences = rabin_karp(s[0],t[j]);
            // for(auto c:ocurrences)cout<<c<<" ";
            int x = 1;
            vector<int> bk(b,0);
            for(auto x:ocurrences)bk[x]++;
            while(x<r && j+x<a && ocurrences.size()){
                ocurrences = rabin_karp(s[x],t[j+x]);   
                for(auto x:ocurrences)bk[x]++;
                x++;
            }
            // for(auto c:bk)cout<<c<<" ";
            for(int i = 0;i<b;i++)if(bk[i] == r)cont++;
        }
        cout<<cont<<endl;
    }
    return 0;
}