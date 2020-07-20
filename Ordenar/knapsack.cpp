#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int knapSack(int W, vector<int> wt, vector<int> val, int n)
{
   int i, w;
   int K[n+1][W+1];
 
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
 
   return K[n][W];
}
 
int main()
{
	vector<int> val;
	vector<int> wt;
	int W,v,weight,N;
	cin>>W>>N;
	for(int i = 0;i<N;i++){
    	cin>>v>>weight;
    	val.push_back(v);
    	wt.push_back(weight);
    
	}
    cout<<knapSack(W, wt, val, N);
    return 0;
}
