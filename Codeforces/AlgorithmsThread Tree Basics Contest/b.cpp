#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
const int maxn = 300007;
#define x first
#define y second
vector<int> graph[maxn];
void add_edge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
vector<int> depth(maxn);
vector<int> parent(maxn);
int pa[25][maxn];
int q[maxn];
int top;
vector<int> dist(maxn);
const int INF = 10000000;
void dfs(int u,int p = -1){
    parent[i] = p;
    for(auto v:graph[u]){
        if(v == p)continue;
        dfs(v,u);
    }
}
pair<int,int> bfs(int s,int n){
    for(int i = 0;i<n;i++)dist[i] = INF;
    q[top++] = s;
    dist[s] = 0;
    pair<int,int> ans;
    ans.x = -1;
    for(int i = 0;i<top;i++){
        int u = q[i];
        for(auto v:graph[u]){
            if(dist[v]< dist[u]+1)continue;
            dist[v] = dist[u]+1;
            q[top++] = v;
            if(dist[v]>ans.y){
                ans.y = dist[v];
                ans.x = v; 
            }
        }
    }
    return ans;
}


int main(){__
    int n,u,v;
    cin>>n;
    if(n == 1)return cout<<1<<endl,0;
    for(int i = 0;i<n-1;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v);
    }
    auto dim = bfs(0,n);
    top = 0;
    dim = bfs(dim.x,n);   
    dfs(dim.x);
    for(int i = 0;i<n;i++)cout<<dist[i]<<" ";
    cout<<endl; 
    for(int i = 0;i<n;i++){
        if(dist[i] == dim.y|| dist[i]== 0|| parent[i] == parent[dim,])cout<<dim.y+1<<endl;
        else cout<<dim.y<<endl;
    }
    return 0;
}

