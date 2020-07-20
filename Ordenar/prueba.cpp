
#include <stdio.h>
#include <stdlib.h>
int main(){
	int i = 0,n = 10;
	char c;
	char cad[n];
	for (; i < n && (c=getchar())!=EOF && c!='\n'; i++) 
       cad[i] = c; 
	printf("%s",cad);
	return 0;
}
	
