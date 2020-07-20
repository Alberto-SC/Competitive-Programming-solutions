#include <stdio.h>
int main(){
   long n;
   scanf("%ld",&n);
   while(n>0){
     scanf("%ld",&year);
     if ((((year % 4)==0) && ((year % 100)!=0 ))||((year % 100) == 0 && (year % 400)==0))
       printf("S\n");
     else
       printf("N\n");
     n--;
   }
}
