#include <stdio.h>
#include <stdlib.h>
int main(){
	int c,i,m,j = 0,k,min= 0,max = 0,l,z,w;
	int **r;
	int ***s;
	scanf("%d",&c);
	r =(int **)malloc(sizeof(r));
	s =(int ***)malloc(sizeof(s));
		for(i = 0;i<c;i++){
			s= (int***)realloc(s,(c+1)*sizeof(s));
			scanf("%d",&m);
			j = 0;
			do{		
				r[j] = (int*)malloc(sizeof(int)*2);			
				scanf("%d %d",&r[j][0],&r[j][1]);
				r = (int**)realloc(r,(j+2)*sizeof(int*));
				j++;  
			
			}while(r[j-1][0]!= 0 && r[j-1][1]!=0);
			for(k = 0;k<m;k++){
				for(l = 0;l<j;l++){
					if(r[l][0]<= k && r[l][1]>k){
						if(r[l][1]> max)
						max = r[l][1];				
						s[i][min+1] = (int*)malloc(sizeof(int)*2);
						s[i][min+1][0]= r[l][0];
						s[i][min+1][1]= r[l][1];
					
					}
				}
				s[i]= (int**)realloc(r,(min+2)*sizeof(int*));	
				if(max != 0){
					min++;
					k+=max;
					printf("%d",min);
					s[i][0][0] = min;
				}
				else {
				k = m;
				}		
			}
		if(min != 0 && s[i][min+1][1]<m){

			free(s[i]);
			s[i][0] = (int*)malloc(sizeof(int));
			s[i][0][0] = 0;
			
		}
		free(r);
		
	}
	for(i = 0;i<c;i++){
		m = s[i][0][0];
		if(m == 0){
			printf("0");
		}
		else{
			printf("%d\n",m);
		for(j = 1;j<m+1;j++){
			printf("%d %d\n",s[i][j][0],s[i][j][1]);
		}
		}
		printf("\n");
	}
	free(s);
	return 0; 
}

