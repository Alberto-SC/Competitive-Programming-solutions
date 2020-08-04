#include <bits/stdc++.h>
using namespace std;
typedef long long lli;
const lli inf = 1000000000000;
lli dist[50][50];
lli bestd[50][50];
int n;
void floyd(){
    for(int k = 0;k<26;k++){
        for(int i = 0;i<26;i++){
            for(int j = 0;j<26;j++){
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}
char best[30][30];

int main(){
    lli q,c;
    char a,b;
    string s,t;
    cin>>s>>t;
    cin>>q;
    for(int i = 0;i<26;i++)for(int j = 0;j<26;j++)dist[i][j] = inf;
    for(int i = 0;i<26;i++)dist[i][i]= 0;
    for(int i = 0;i<q;i++){
        cin>>a>>b>>c;
        dist[a-'a'][b-'a'] = min(dist[a-'a'][b-'a'],c);
    }
    floyd();
    if(s.size()!= t.size())return cout<<-1<<endl,0;
    lli ans = 0;
    string final = s;
    for(int i = 0;i<26;i++){
        for(int j = 0;j<26;j++){
            lli mn = inf;
            for(int k = 0;k<26;k++){
                if(dist[i][k] + dist[j][k]<mn){
                    mn = dist[i][k] +dist[j][k];
                    best[i][j] = char('a'+k);
                }  
            }
            bestd[i][j] = mn;
        }
    }
    for(int i = 0;i<s.size();i++){
        ans += bestd[s[i]-'a'][t[i]-'a'];
        final[i] = best[s[i]-'a'][t[i]-'a'];
        if(ans>=inf)return cout<<-1<<endl,0;

    }
    cout<<ans<<endl;
    cout<<final<<endl;
    return 0;
}