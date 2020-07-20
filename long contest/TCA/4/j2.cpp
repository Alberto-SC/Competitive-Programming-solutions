#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
typedef long long int lli;
const lli maxn = 300007;
vector<lli> graph[maxn];
vector<pair<lli,lli>> querys[maxn];

lli n;
void add_edge(lli u,lli v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
vector<lli> ans(maxn);
vector<lli> levels(maxn);
void dfs(lli u,lli p =-1,lli lvl = 0,lli sum = 0){
    for(auto q:querys[u]){
        levels[lvl]+=q.y; 
        if(lvl+q.x+1<n)
            levels[lvl+q.x+1] -= q.y;
    }
    ans[u]= sum+levels[lvl];
    for(auto v:graph[u]){
        if(v == p)continue;
        dfs(v,u,lvl+1,sum+levels[lvl]);
    }
    for(auto q:querys[u]){
        levels[lvl]-=q.y;
        if(lvl+q.x+1<n)
            levels[lvl+q.x+1]+=q.y;
    }
}
int main(){__
    lli q,u,v,h,val;
    cin>>n;
    for(lli i = 0;i<n-1;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v);
    }
    cin>>q;
    for(lli i = 0;i<q;i++){
        cin>>v>>h>>val;
        v--;
        querys[v].push_back({h,val});
    }
    dfs(0);
    for(lli i = 0;i<n;i++)cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}