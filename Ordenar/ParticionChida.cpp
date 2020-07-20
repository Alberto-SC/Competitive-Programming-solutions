#include <stdlib.h>
#include <iostream>
#include <cmath>
int DP[101];
using namespace std;
int s(int n){
	int gpn1,gpn2;
	if(n < 0 ) return 0; 
	if(DP[n] != 0)	return DP[n];
	for(int i = 1 ; i<= ceil(sqrt(n)) ; i++){
		gpn1 = (i*((3*i)-1))/2;     gpn2 = (-i*((3*-i)-1))/2;
 		if(i%2 == 0) DP[n] -= s(n-gpn1) + s(n-gpn2);
 		else DP[n] = DP[n] += s(n-gpn1) + s(n-gpn2);	
	}
	return DP[n];
}
int main(){
	int n;
	DP[0] =1;
	for(int i = 1; i<103;i++){
		DP[i] = 0;
	}
	cin>>n;
	cout<<s(n);
}