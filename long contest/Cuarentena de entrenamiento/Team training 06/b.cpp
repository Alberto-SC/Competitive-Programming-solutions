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
        bool flag = false;
        lli div= 0,res = 0;
        map<lli,lli> mp;
        lli ans = 1;
        bool find = false,complete = false;
        lli cont = 0;
        vector<lli> pref;
        pref.push_back(1);
        if(a>b)div = a/b,a = a-(b*div),a*=10;
        while(1){ 
            div = a/b;
            cont++;
            if(div == 0)ans*=7;
            else 
                ans*=div;
            pref.push_back(ans);
            ans%=m;
            a = a-(b*div);
            res = a;
            a*=10;
            // cout<<div;
            if(res == 0){complete = true;break;}
            if(mp.count(res))break;
            if(cont== n){find = true;break;}
            mp[res] = cont;
        }
        // cout<<endl;
        if(find)cout<<ans<<endl;
        else if(complete){
            // cout<<"NO ciclo"<<endl;
            lli x = ans;
            lli nn = n-cont;
            lli y = pow_mod(7,nn);
            x*=y;
            x%=m;
            cout<<x<<endl;
        }
        else{
            // cout<<"ciclo"<<endl;
            // cout<<cont<<" "<<res<<endl;
            // for(auto c:pref)cout<<c<<" ";
            // cout<<endl;
            lli x = pref[mp[res]];
            // cout<<x<<" "<<mp[res]<<endl;
            lli ciclo= pref[cont];
            // cout<<ciclo<<endl;
            ciclo *= pow_mod(pref[mp[res]],m-2);
            ciclo%=m;
            // cout<<ciclo<<endl;
            lli nn = n-mp[res];
            lli sz = cont-mp[res];
            // cout<<nn<<" "<<sz<<" "<<nn/sz<<" "<<nn%sz<<endl;
            x*= pow_mod(ciclo,nn/sz);
            x%=m;
            lli y = pref[mp[res]+(nn%sz)];
            // cout<<y<<endl;
            y*= pow_mod(pref[mp[res]],m-2);
            y%=m;
            x*=y;
            x%=m;
            cout<<x<<endl;
        }
    }
    return 0;
}
