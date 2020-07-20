#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void quitar(char*,char*);
int main(){
	char *a;
	char *b;
	scanf("%[^\n]",&a);
	getchar();
	scanf("%s",&b);
	
	quitar(a,b);
	return 0;
}

void quitar(char *a,char*b){
	int k = 0;
	int y = 0;
	char c[100000];
	for(int i = 0; i<strlen(a) ;i++){
		for(int j = 0; j<strlen(b);j++){
				if(a[i] == b[j])
				y = 1;		
		}
			if(y == 1){
				y = 0;
				continue;
			}
			if(y == 0){
			c[k] = a[i];
			k++;
		}
		y = 0;
		}
		a = c;
		printf("%s",a);
	}
