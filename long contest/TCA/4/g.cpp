#include <bits/stdc++.h>
using namespace std;
const int maxn = 100007;
struct Edge{
    int u,v,c;
    bool operator < (const Edge A ){
        return c<A.c;
    }
};
vector<int> special(maxn,0);
vector<Edge>edges;
vector<int> sz(maxn,1);
vector<int> p(maxn);

int raiz(int u){
    return u == p[u]?u:p[u] = raiz(p[u]);
}

void union_by_size(int u,int v){
    u = raiz(u);
    v = raiz(v);
    if(sz[v]>sz[u])swap(u,v);
    sz[u] += sz[v];
    p[v] = u;
    special[u]+=special[v];
}

int n,k,m;
int kruskal(){
    sort(edges.begin(),edges.end());
    for(int i = 0;i<m;i++){
        if(raiz(edges[i].u)== raiz(edges[i].v))continue;
        union_by_size(edges[i].u,edges[i].v);
        if(special[raiz(edges[i].u)] == k)return edges[i].c;
    }

}

int main(){
    int u,v,c;
    cin>>n>>m>>k;
    iota(p.begin(),p.end(),0);
    for(int i = 0;i<k;i++){
        cin>>v;
        v--;
        special[v] = 1;
    }
    for(int i = 0;i<m;i++){
        cin>>u>>v>>c;
        u--,v--;
        edges.push_back({u,v,c});
    }
    
    int x = kruskal();
    for(int i = 0;i<k;i++)cout<<x<<" ";
    cout<<endl;
    return 0;
}