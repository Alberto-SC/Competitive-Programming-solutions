#include <bits/stdc++.h>
using namespace std;
int main(){
    int t,n1,n2;
    cin>>t;
    while(t--){
        cin>>n1>>n2;
        cout<<__gcd(n1,n2)<<"\n";
    }
    return 0;
}