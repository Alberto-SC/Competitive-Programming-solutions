#include <bits/stdc++.h>
using namespace std;
vector<int> z;
void z_func(string s){
    int n = s.length();
    z[0] = 0;		
    for (int i = 1, l = 0, r = 1; i < n; i++, r = i < r ? r : i)
        for (z[i] = min(r - i, z[i - l]); s[i + z[i]] == s[z[i]]; z[i]++, r = i + z[i], l = i);

}

int main(){
    string s,p;
    cin>>s>>p;
    int n = s.size()+p.size()+1;
    int match = p.size();
    string zf= p+"$"+s;
    z.resize(n);
    z_func(zf);
    cout<<match<<endl;
    for(auto c: z)cout<<c<<" ";
    for(int i = match+1;i<n;i++)
        if(z[i] == match)cout<<"find in index :"<<i-match<<endl;
    cout<<endl;
    return 0;
}