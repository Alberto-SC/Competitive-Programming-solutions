#include <bits/stdc++.h> 
using namespace std;
typedef long long int lli;
vector<lli> DP(1000007,-1);
const int mod = 1000000007;
int S(int n,bool three){ 
    cout<<n<<endl;
    if(n == 1)return 1;
    if(n<0)return 0;   
    if(DP[n] != -1)return DP[n];
    DP[n] = S(n-1,false);
    DP[n] = (DP[n]+S(n-2,false))%mod;
    if(!three) DP[n] = (DP[n]+S(n-3,true))%mod;
    return DP[n]; 
} 
  
int main() { 
    DP[1] = 1;
    DP[2] = 2;
    DP[3] = 4;
    int n;
    cin>>n;
    cout << S(n,false)<<"\n"; 
    return 0; 
} 