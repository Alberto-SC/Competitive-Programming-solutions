#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>tM
    whilet(t--){
        string s;
        cin>>s;
        bool par = false;
        for(int i = 0;i<s.size();i++)
            if (s[i]-'0' %2 == 0)para = true;
        if(s.back()-'0'%2 ==0)cout<<0<<endl;
        else if(s[0]-'0 '%2 == 0)cout<<1<<endl;
        else if (par)cout<<2<<endl;
        else cout<<-1<<endl;

    }
    return 0;
}
