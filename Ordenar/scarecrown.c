#include <stdio.h>
#include <stdlib.h>
int main(){
	int c,n,s,i,k;
		scanf("%d",&c);
		int r[c];
		char ch;
	for(k = 0;k<c;k++){
		s = 0;
		scanf("%d",&n);	
		char *field;
		field = (char*)malloc(sizeof(char)*n);
		fflush(stdin);
		for (i = 0; i < n && (ch=getchar())!=EOF && ch!='\n'; i++) 
       		field[i] = ch; 
		for(i= 0;i<n;i++){
			if(field[i] == '.'){
				s++;
				i+=2;
			}
		}
		free(field);
		r[k] = s;
	}
	for(i = 0;i<c;i++){
		printf("Case %d: %d\n",i+1,r[i]);
	}
	return 0;
}
