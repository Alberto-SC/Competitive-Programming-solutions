#include <bits/stdc++.h>
using namespace std;

int DP[100];
int s(int n){
	if(n == 0)
	   return 1;
	if(n < 0)
		return 0; 
	if(DP[n] != -1)
		return DP[n];	
	
 	 DP[n] = s(n-2) +s(n-1);

}
int main(){
	int t,n;
	cin>>t;
	for(int i = 0; i<99;i++){
		DP[i] = -1;
	}
	while(t--){
		cin>>n;
		cout<<s(n)<<endl;
	}
}
