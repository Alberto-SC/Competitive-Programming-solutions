#include <bits/stdc++.h>
using namespace std;int n, S;             
const int MAXN = 1000;
const int MAXW = 1000;                           //n &mdash; number of coin types, S &mdash; desired overall weight
int wgt[MAXN];                                   //array of coin weights (W); for example: {1, 3, 5};
int mink[MAXW];                                  //array of DP results (k); look above for the example;

int main(){
    int n,S;
    cin>>n>>S;
    for(int i = 0;i<n;i++)cin>>wgt[i];
    mink[0] = 0;                                   //base of DP: 0 weight can be achieved by 0 coins
    for (int P = 1; P<=S; P++) {                   //iterate through all the states
        int minres = 1000000000;                    
        for (int i = 0; i<n; i++) if (wgt[i] <= P) { //suppose that the coin with weight wgt[i] is the last
        int tres = mink[P - wgt[i]] + 1;           //the number of coins with the coin is greater by one
        if (minres > tres) minres = tres;          //choose the minimal overall number of coins among all cases
        }
        mink[P] = minres;                            //store the result in mink array
    }
    int answer = mink[S];   
}