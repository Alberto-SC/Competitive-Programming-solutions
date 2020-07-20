#include <stdlib.h>
#include <stdio.h>
#include <iostream>
int DP[101];
using namespace std;
void ini(){
	for(int i = 0; i<101;i++){
		DP[i] = -1;
	}
}
int s(int n){
	if(n == 0)return 1;
	if(DP[n] != -1)return DP[n];	
	for(int i = 1;i<=n;i++){
 	 	if(i == 1) DP[n] = s(n-i);
 	 	else DP[n]+= s(n-i);
	}
	return DP[n];
}
int main(){
	int n = 5;
	ini();
	printf(" %d \n",s(n));
	for(int i = 0;i<=n;i++)
		cout<<DP[i]<<" ";
}