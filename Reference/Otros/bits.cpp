#include <bits/stdc++.h>
using namespace std;
int main(){
    int m = 7,n;
    cin>>n;
    for (int m=0; m<(1<<n); ++m){
        for (int s=m; s; s=(s-1)&m)cout<<s<<" ";
        cout<<endl;
    }

    return 0;
}