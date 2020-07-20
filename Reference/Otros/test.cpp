#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int ans = 0;
    for(int i = 2;i<n;i++){
        ans+= n/i;
    }
    cout<<ans<<endl;
    return 0;
}