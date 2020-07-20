#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int main(){
	int cn[9];
	int n = 1,yes = 1,k,p,pot;
	for(int i = 0; i<9;i++){
		scanf("%d",&cn[i]);
	}
	while(yes == 1){
		p = n;
		do{
			if(floor(log10(p)) == log10(p)){
				pot = log10(p);
				k = floor(p/pow(10,pot));		
				if(--cn[k] == 0){
					yes = 0;
					pot = 0;
					continue;
				}
				cn[k]--;
				if(cn[0]-pot <0){
					yes = 0;
					pot = 0;
					continue;
				}
				cn[0] = cn[0]-pot; 
				pot = 0;
			}
			else if(floor(log10(p)) != log10(p)){
				pot = floor(log10(p));
				k = floor(p/pow(10,pot));
				if( p-(k *pow(10,pot)) == 0){
					if(cn[0]-pot <0){
						yes = 0;
						pot = 0;
						continue;
					}
					cn [0]  = cn[0]-pot;
				}	
				p = p-(k *pow(10,pot));	
				if(pot != 0){
					pot--;
				}
				if(--cn[k] == 0){
					yes = 0;
					continue;
				}
				cn[k]--;
			}				
		}while(pot != 0);
		if(yes == 0){
			continue;
		}
		n++;
	}
	printf("%d",n-1);
	return 0;
}
