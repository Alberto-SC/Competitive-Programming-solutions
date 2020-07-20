#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void Shell(int *A,int n);
int main(int arg, char*argv[]){
	int i,n;
	n = strtol(argv[1],NULL,10);
	int *A;
	A = (int*)malloc(sizeof(int)*n);
  	for(i = 0;i<n;i++){
  		scanf("%d",&A[i]);
	  }
	  
  	Shell(A,n);
  	for ( i = 0; i<n; i++) { 
    	printf("%d\n", A[i]);
  	}
  	return 0;
}

void Shell(int *A,int n){
  int k,temp,b,i,j;
  k=trunc(n/2);
  while (k>=1) {
    b=1;
    while (b!=0) {
      b=0;
      for (i=k; i<n; i++) {
        if(A[i-k]>A[i]){
          temp=A[i];
          A[i]=A[i-k];
          A[i-k]=temp;
          b=b+1;
        }
      }
    }
    k=trunc(k/2);
  }
}	
