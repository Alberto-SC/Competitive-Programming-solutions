#include <stdio.h>
void Seleccion(int *A,int n);
int main(){
  int *a = (int*)malloc(10000000*sizeof(int));
  for(unsigned long int i=0; i<10000000;i++)
    scanf("%d\n",&a[i]);
  Seleccion(a,10000000);
  for (int i = 0; i<10000000; i++) {
    printf("%d\n", a[i]);
  }
  return 0;
}

void Seleccion(int *A,int n){
  int p,temp;
  for(int k=0; k<=n-2; k++){
    p=k;
    for(int i=k+1; i<=n-1; i++){
      if(A[i]<A[p]){
        p=i;
      }
    }
    temp=A[p];
    A[p]=A[k];
    A[k]=temp;
  }
}
