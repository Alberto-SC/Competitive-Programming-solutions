#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli lcm(lli a,lli b){
    return b*(a/__gcd(a,b));
}
int main(){
    lli n,a,b,c;
    cin>>n>>a>>b>>c;
    lli ans1,ans2,ans3;
    lli ab =lcm(a+1,b+1);
    lli ac =lcm(a+1,c+1);
    lli bc =lcm(b+1,c+1);
    if(ab<ac && ab<bc){
        if(ab/a >ab/b)
    }

    cout<<mn<<endl;
    return 0;
}