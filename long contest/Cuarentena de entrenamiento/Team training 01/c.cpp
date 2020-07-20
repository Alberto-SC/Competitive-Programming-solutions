#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int maxn = 100007;
const int maxlog = 20;
vector<int> sz(maxn);
vector<int> padre(maxn);
vector<int> deep(maxn);
vector<pair<int,int>> graph[maxn];
int parent[maxlog][maxn];
int timemx[maxlog][maxn];

int raiz(int v){return  padre[v] == v ?v: padre[v] = raiz(padre[v]);}
 
bool union_find(int u,int v){
    u = raiz(u);
    v = raiz(v);
    if (u != v) {
        if (sz[u] < sz[v])
            swap(u, v);
        padre[v] = u;
        sz[u] += sz[v];
        return true;
    }
    return false;  
}
 
bool conexos(int u,int v){
    u = raiz(u);
    v = raiz(v);
    if(u == v)return true;
    return false;
}

void add_edge(int u,int v,int w){
    graph[u].push_back({v,w});
    graph[v].push_back({u,w});
}

void dfs(int u,int p = -1 ,int h = 0){
    deep[u] = h;
    parent[0][u] = p;
    for(auto v:graph[u]){
        if(v.x == p)continue;
        timemx[0][v.x] = v.y;
        dfs(v.x,u,h+1);
    }
}
int N;
void build(){
    for(int i = 0;i<N;i++)if(deep[i] == -1)dfs(i);
    for(int i = 1;i<maxlog;i++){
        for(int u = 0;u<N;u++){
            if(parent[i-1][u]!= -1){
                parent[i][u] = parent[i-1][parent[i-1][u]]; 
                timemx[i][u] = max(timemx[i-1][u], timemx[i-1][parent[i-1][u]]);
            }
        }
    }
}

int lca(int u,int v){
    int mx = -200;
    if(deep[u] >deep[v])swap(u,v);
    int diff = (deep[v]-deep[u]);
    for(int i = maxlog-1;i>=0;i--){
        if(diff & (1<<i)){
            mx = max(timemx[i][v],mx);
            v = parent[i][v];
        }
    }
    if(u == v)return mx;
    for(int i = maxlog-1;i>=0;i--){
        if(parent[i][v]!= parent[i][u]){
            v = parent[i][v];
            u = parent[i][u];
            mx = max(mx,timemx[i][v]);
            mx = max(mx,timemx[i][u]);
        }
    }
    mx = max(mx, max(timemx[0][u], timemx[0][v]));
    return mx;
}



void init(){
    for(int i = 0;i<N;i++)for(int j = 0;j<maxlog;j++){parent[j][i] = -1;timemx[j][i] =0;}
    for(int i = 0;i<N;i++)deep[i] = -1;
}

int main(){
    int t,u,v,tp,n,m;
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i = 0;i<n;i++)graph[i].clear(),padre[i] = i,sz[i] = 1;
        vector<pair<pair<int,int>,pair<int,int>>> querys;
        for(int i= 0;i<m;i++){
            cin>>tp>>u>>v;
            u--,v--;
            if(tp == 1){
                if(union_find(u,v))
                    add_edge(u,v,i+1);
            }
            // else 
            querys.push_back({{u,v},{tp,i+1}});
            
        }
        N = n;
        init();
        build();
        for(int i = 0;i<n;i++)padre[i] = i,sz[i] = 1;
        for(int i = 0;i<querys.size();i++){
            u = querys[i].x.x;
            v = querys[i].x.y;
            // cout<<u<<" "<<v<<endl;
            int tt = querys[i].y.y;
            tp = querys[i].y.x;
            if(tp ==1){
                union_find(u,v);
            }
            else {
                if(conexos(u,v)){
                    int lc = lca(u,v);
                    // cout<<tt<<" "<<lc<<" "<<u<<" "<<v<<endl;
                    cout<<lc<<endl;
                }
                else cout<<-1<<endl;
            }

        }
    }
    return 0;
}