#include<stdio.h>
int m(int a,int b){ return (a<b)? a: b ;}
int Troto(int S, int t[], int v[], int n){
   int i, s,j,min = 999999,z,w,k,c;
   int Dp[n+1][S+1] = {0};
   for (i = 0; i <= n; i++){	
       for (s = 0; s <= S; s++){
       		c = 0;
            if (i==0 || s==0)
               Dp[i][s] = 0;  
           	else {
				if(Dp[i-1][s] != 0&&s-v[i-1] >= 0)
				Dp[i][s] = m(t[i-1] + Dp[i-1][s-v[i-1]] , Dp[i-1][s]);
				else if(Dp[i-1][s] != 0&&s-v[i-1] < 0)
				Dp[i][s]=m(t[i-1], Dp[i-1][s]);
				else if(Dp[i-1][s] == 0&&s-v[i-1] >= 0 && Dp[i-1][s-v[i-1]] != 0)
				Dp[i][s]=t[i-1] + Dp[i-1][s-v[i-1]];
            	else if(Dp[i-1][s] == 0 && v[i-1]< s)
            	Dp[i][s] = 0;
				else
				Dp[i][s] = t[i-1];
          		
          	}
   		}  	 
       }
	for(i = 0;i<n+1;i++){
		if(Dp[i][S] < min&& Dp[i][S] != 0)
		min = Dp[i][S];
	}
	if(min != 999999)
   return min;
   else 
   return 0;
}

int main()
{	
	int n ,s;
	scanf("%d %d",&n,&s);
	int v[n];
    int t[n];
	for(int i = 0;i<n;i++){
		scanf("%d %d",&v[i],&t[i]);
	}
    printf("%d", Troto(s,t,v,n));
    return 0;
}
