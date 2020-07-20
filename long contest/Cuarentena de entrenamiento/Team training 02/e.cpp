#include <bits/stdc++.h>
using namespace std;
#define first fi
#define second se
int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<int> ac(n);
    vector<int> last(n);
    ac[0] = 1;
    int x = 0,y = 0;
    map<pair<int,int>,int>mp;
    mp[{0,0}] = 1;
    int ans = 1;
    int cont = 0;
    vector<pair<int,int>> pos(n);
    for(int i = 0;i<n;i++){
        cont++;
        if(s[i] == 'R')
            x++;
        if(s[i] == 'L')
            x--;
        if(s[i] == 'U')
            y++;
        if(s[i] == 'D')
            y--;
        // cout<<x<<" "<<y<<endl;
        pos[i] = {x,y};
        if(mp.find({x,y})!= mp.end()){
            last[i] = mp[{x,y}];
            ac[i] = ac[i-1];
            ans = max(ans,cont);
            cont = 0;
        }
        else {
            ac[i] = ac[i-1]+1;
            mp[{x,y}] = i+1;
        }
    }
    cout<<n-ans<<endl;

    // cout<<endl;
    // int ans = 1;
    // int cont = 1;
    // for(auto c:ac)cout<<c<<" ";
    // cout<<endl;
    // for(auto c:last)cout<<c<<" ";
    // cout<<endl;
    // for(int i = 1;i<n;i++){
    //     if(ac[i] == ac[i-1]+1)cont++;
    //     else {
    //         bool flag = false;
    //         if(s[last[i]-1] == R){
    //             if(mp[{pos.fi-1},pos.se]!= mp.end())
    //         } 
    //         if(s[last[i]-1] == R){

    //         } 
    //         if(s[last[i]-1] == R){

    //         } 
    //         if(s[last[i]-1] == R){

    //         } 
    //         if(!flag)
    //         cont-= last[i];
    //         cont++;
    //     }
    //     ans = max(cont,ans);
    // }
    // cout<<ans<<endl;
    return 0;
}