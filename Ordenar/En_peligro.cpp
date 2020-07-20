#include <stdio.h>
#include <math.h>
int main(){
	long long  r,N,N9;
	scanf("%lld",&N);
	for(int i = 1;i<17;i++){
		if(pow(10,i) == N+1){
		N9 = i;
		i = 19;
	}
}
	printf("%lld",((45*(long long)pow(10,N9-1))*N9));
	
	return 0;
}
