#include <stdlib.h>
#include<stdio.h>

void sub(int o[],int s,int n,int b,int *r){
	for(int i = 0;i<n;i++){
		if(s-(o[i])>=b && o[i]!= 0){
			s = s-(o[i]);
			o[i] = 0;
			sub(o,s,n,b,r);
		}
	}
	if(s<*r)
	*r= s;
}
int main()
{	
	int n,i;
	long s= 0,b;
	int *r;
	scanf("%d %l",&n,&b);
	int o[n];
	for(i=0;i<n;i++){
		scanf("%d",&o[i]);
		s+=o[i];
	}
	printf("%\n",s);
	sub(o,s,n,b,r);
    printf("%d",*r-b);
    return 0;
}
