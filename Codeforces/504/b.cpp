#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
int main(){
    lli a,b;
    cin>>b>>a;
    lli x = abs((a-1)-b);
    if(x<b)cout<<(b-x)/2;
    else cout<<0<<endl;
    return 0;
}