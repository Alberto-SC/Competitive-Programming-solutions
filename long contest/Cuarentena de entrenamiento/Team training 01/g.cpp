#include <bits/stdc++.h>
using namespace std;
const int maxn = 110007;
#define x first
#define y second
typedef long long int lli;
const lli INF = 1ll<<60; 
vector<pair<lli,pair<lli,lli>>> graph[maxn];

lli t,n,m,k;
void add_edge(lli u,lli v,lli c,lli w){
    graph[u].push_back({v,{c,w}});
    graph[v].push_back({u,{c,w}});
}
bool dijkstra(lli mxw){
    vector<lli> D(maxn,0);
    for(int i=1;i<n;i++)D[i] = INF;
    priority_queue<pair<int,lli>,vector<pair<int,lli>>,greater<pair<int,lli>>> q;
    q.push({0,0});
    while(!q.empty()){
        pair<lli,int> p = q.top();
        q.pop();
        int u = p.y;
        lli dist = p.x;
        if(dist > D[u]) continue;
        for(auto pr: graph[u]){
            if(pr.y.y>mxw)continue;
            int v = pr.x;
            lli next_dist = dist + pr.y.x;
            if(next_dist < D[v]){
                D[v] = next_dist;
                q.push({next_dist,v});
            }
        }
    }
    if(D[n-1]<k)return true;
    return false;
}
int main(){
    lli u,v,c,w;
    cin>>t;
    while(t--){
        cin>>n>>m>>k;
        for(int i = 0;i<n;i++)graph[i].clear();
        lli mx = -1;
        for(int i = 0;i<m;i++){
            cin>>u>>v>>c>>w;
            u--,v--;
            mx = max(mx,w);
            add_edge(u,v,c,w);   
        }
        int l = 1;int r = mx;
        while(l+1<r){
            int m = (l+r+1)>>1;
            bool possible = dijkstra(m);
            // cout<<m<<" "<<possible<<endl;
            if(possible)
                r = m;
            else l = m;
        }
        if(!dijkstra(r))r = -1;
        cout<<r<<endl;
    }
    return 0;
}