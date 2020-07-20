#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,n,ai;
    cin>>r>>n;
    vector<int> b(r+1,0);
    for(int i =0;i<r;i++){
        cin>>ai;
        b(ai)++;
    }
    boll one =false;
    for(int i =1;i<=r;i++){
        if(!b[i])cout<<i<<" ",one =true;
    }
    if(!one)cout<<"*"<<endl;
    return 0;
}