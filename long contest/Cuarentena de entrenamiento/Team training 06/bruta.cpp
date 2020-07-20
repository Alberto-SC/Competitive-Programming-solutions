#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
const lli m =  999999937;

lli pow_mod(lli a,lli b){
    lli x = 1;
    while(b){
        if(b&1)x = (x*a)%m;
        a = (a*a)%m;
        b>>=1;
    }
    return x;
}
int main(){
    lli t,a,b,n;
    cin>>t;
    while(t--){
        cin>>a>>b>>n;
        lli div= 0,res = 0;
        lli ans = 1;
        lli cont = 0;
        bool complete = false;
        if(a>b)div = a/b,a = a-(b*div),a*=10;
        while(1){ 
            div = a/b;
            cont++;
            if(div == 0)ans*=7;
            else 
                ans*=div;
            ans%=m;
            a = a-(b*div);
            a*=10;
            // cout<<div;
            if(cont== n){break;}
        }
        // cout<<endl;
        cout<<ans<<endl;
    }
    return 0;
}
