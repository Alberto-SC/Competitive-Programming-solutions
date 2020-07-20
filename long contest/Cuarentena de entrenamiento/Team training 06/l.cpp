#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long lli;
lli DP[10007];
lli s(lli n){
	if(n == 0)
	   return 1;
	if(n < 0)
		return 0; 
	if(DP[n] != -1)
		return DP[n];	
	
 	DP[n] = s(n-2) +s(n-1);
    return DP[n];
}


int main(){
	lli t,n;
    cin>>t;    
	for(lli i = 0; i<10007;i++)
		DP[i] = -1;
    while(t--){
	    cin>>n;
	    s(n);
        cout<<DP[n]<<endl;
    }
}