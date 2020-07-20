#include <stdio.h>
#include <stdio.h>
#define MAX 100
long long DP[200];
void ini(){
	int i; 
	for(i = 0;i<MAX;i++){
		DP[i] = 0;
			}
}
long long fib(int n){
	if(DP[n] == 0){
		if(n <= 1)
			DP[n] = n;
		else
			DP[n] = fib(n-1) + fib(n-2);
	}	
	return DP[n];
}
int main(){
	ini();
	printf("  %lld  ",fib(200));
}
