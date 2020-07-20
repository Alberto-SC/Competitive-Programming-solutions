#include <stdlib.h>
#include <stdio.h>
int *DP;
int s(int n){
	if(n<=4)
	return n;
	if(DP[n] != 0)
		return DP[n];
	DP[n] = s((int)n/2)+ s((int)n/3)+ s((int)n/4);
	if(DP[n]>n)
		return DP[n];
	else
		return n;
}
int main(){
	
	int n;
	while( scanf("%d",&n)!=EOF){
		DP = (int*)calloc(n,sizeof(int));
		printf("%d", s(n));
	}
}
