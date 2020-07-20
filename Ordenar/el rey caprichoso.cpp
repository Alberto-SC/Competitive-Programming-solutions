#include <stdlib.h>

int main(){
	int n,max = 0,ni,c,nm,nmax1,nmax2,r,r1= 0,r2 = 0;
	int b[1000000];
	scanf("%d",&n);
	for(int i = 0;i<n;i++){
		scanf("%d",&ni);
		b[ni]++;
		if(ni > max)
		max = ni;
	}
	for(i = max;i>0;i--){
		nm = (max/i)*i;
		for(int j= 0; j<nv;j++){
			if(b[i-(j*i)]>0 && b[i-(j*i)]<2)
			c= c+ b[i-(j*i)];
			if(b[i-(j*i)]>2)
			r = (i-(j*i))* (i-(j*i));
		}
		if(c >=2)
			i = 0;
	}
	if(c> 2){
		printf("%d",r);
	}
	if(c == 2){
		printf("%d")
	}
	
	
}
