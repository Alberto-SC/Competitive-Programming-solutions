#include <bits/stdc++.h>
using namespace std;
int bucket[27];
bool comp(char a,char b){
    return bucket[a-'a']<bucket[b-'a'];
}
int main(){
    int t;
    cin>>t;
    while(t--){
        string order,s;
        cin>>order>>s;
      	int n = order.size();
        for(int i = 0;i<n;i++)
            bucket[order[i]-'a'] = i;
        sort(s.begin(),s.end(),comp);
        cout<<s<<"\n";
    }

    return 0;
}
