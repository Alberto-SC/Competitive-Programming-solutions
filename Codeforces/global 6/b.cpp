#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    unsigned long long int x;
    cin>>n;
    for(int i = 0;i<=n;i++){
        cin>>x;
        if(x<14)cout<<"NO"<<endl;
        else{
            unsigned long long div = floor(x/14);
            if (x-div*14>6)cout<<"NO"<<endl;
            else if(x-div*14 == 0)cout<<"NO"<<endl;
            else cout<<"YES"<<endl;
        }
    }
    return 0; 
}