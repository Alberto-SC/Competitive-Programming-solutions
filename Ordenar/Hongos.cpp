#include <stdio.h>
#include <stdlib.h>  
int main(){
	int c,m,nc,nh,nd,temp;
	char o;
	
	scanf("%d",&c);
	int* celdas = (int*)malloc(c*sizeof(int));
	for(int i = 0;i<c;i++){
		celdas[i] = 0;
	}
	scanf("%d",&m);
	for(int i= 0;i<m;i++){
		fflush(stdin);
		scanf("%c",&o);
		fflush(stdin);
		printf("     %c",o);
		if(o == 'A'){
			scanf("%d %d",&nc,&nh);
			fflush(stdin);
			celdas[nc-1] = celdas[nc-1]+nh;
		}
		if(o == 'B'){
			scanf("%d",&nd);
			fflush( stdin );
			for(int i = 0;i<c ;i++){
				printf("%d ",celdas[i]);
				}
				printf("\n");
				temp = celdas[1];
			for(int d = 0;d<nd;d++){
				for(int ac = 0;ac<c ;ac++){
					if(celdas[ac] != 0 && ac == c-1&&temp != 0){
						c++;
						celdas = (int*) realloc(celdas,c*sizeof(int));
						celdas[ac +1] =  temp+ celdas[ac];
						ac++;
					}		
					if(celdas[ac] != 0){
						celdas[ac +1] =  temp+ celdas[ac];
						temp = celdas[ac+1]-celdas[ac];
					}			
				}
				for(int i = 0;i<c ;i++){
				printf("%d ",celdas[i]);
				}
				printf("\n");
			}
		}
		}
		printf("\n\n\n");
		for(int i = 0;i<c ;i++){
			printf("%d ",celdas[i]);
			
		}
	
	return 0;
}
