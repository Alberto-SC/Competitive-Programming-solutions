#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,t,steps;
    cin>>n>>t;
    vector<vector<int>> times(n,vector<int>(t));

    for(int i = 0;i<n;i++){
        for(int j = 0;j<t;j++)
            cin>>times[i][j];
        cin>>steps;
        times[i][0] = times[i][0]*steps;
        for(int j = 1;j<t;j++)
            times[i][j] = times[i][j]*steps+ times[i][j-1];
    }
    vector<int> leadings(n+1,0);
    for(int i = 1 ;i<t-1;i+=2){
        int mx = -10;
        for(int j = 0;j<n;j++)
            mx = max(times[j][i],mx);
        for(int j = 0;j<n;j++)
            if(times[j][i] == mx)leadings[j]++;
    }
    int mx = -10;

    for(int i = 0;i<n;i++)
        mx = max(mx,leadings[i]);
    for(int i = 0;i<n;i++)
        if(leadings[i] == mx){cout<<i+1<<"\n";break;}
    return 0;
}