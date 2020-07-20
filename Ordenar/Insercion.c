#include <stdlib.h>
#include <stdio.h>
void Insercion(int *A,int n);
int main(){
  int *a = (int*)malloc(10000000*sizeof(int));
  for(unsigned long int i=0; i<10000000;i++)
    scanf("%d\n",&a[i]);
  Insercion(a,10000000);
  for (int i = 0; i<10000000; i++) {
    printf("%d\n", a[i]);
  }
  return 0;
}

void Insercion(int *A,int n){
  int j,temp;
  for(int i=0; i<=n-1; i++){
    j=i;
    temp=A[i];
    while(j>0&&temp<A[j-1]){
      A[j]=A[j-1];
      j--;
    }
    A[j]=temp;
  }
}
