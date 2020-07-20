#include <stdio.h>
#include <stdlib.h>

int main(){
	int c,n,s = 0,i,j;
	char ch;
	char *field;
	field = realloc(NULL,sizeof(char));
		scanf("%d",&c);
		int r[c];
	for(i = 0;i<c;i++){
		scanf("%d",&n);
		for(j = 0;j<n;j++){
			scanf("%c",&field[n]);	
		}
		for(j= 0;j<n;j++){
			if(field[n] == '.'){
				s++;
				n+=3;
			}
			if(field[n] == '#'){
				continue;
			}
		}
		printf("\n%s\n",field);
		r[i] = s;
		s = 0;
		fflush(stdin);
		free(field);
	}
	for(i = 0; i<c; i++){
		printf("%d\n",r[i]); 
	}
	return 0;
}
