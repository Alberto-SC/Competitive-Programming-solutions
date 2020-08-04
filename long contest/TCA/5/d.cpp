#include <bits/stdc++.h>
using namespace std;
const int maxn = 300007;
#define endl '\n'
#define x first
#define y second
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
vector<pair<int,int>> graph[maxn];
void add_edge(int u,int v,int c){
    graph[u].push_back({v,c});
    graph[v].push_back({u,c});
}
struct Edge {
    int u,v,c;
    bool operator <(const Edge A){
        return c<A.c;
    }
};
int DP[maxn];

int main(){__
    int n,u,v,c,m;
    cin>>n>>m;
    vector<Edge> w[maxn];
    for(int i= 0;i<m;i++){
        cin>>u>>v>>c;
        u--,v--;
        w[c].push_back({u,v,c});
    }
    vector<int> temp(maxn,0);
    for(int i = 1;i<maxn;i++){
        int x,y;
        int sz = w[i].size();
        for(int j = 0;j<sz;j++)temp[w[i][j].v] = 0;
        for(int j = 0;j<sz;j++)temp[w[i][j].v] = max(temp[w[i][j].v],DP[w[i][j].u]+1);
        for(int j = 0;j<sz;j++)DP[w[i][j].v] = max(temp[w[i][j].v],DP[w[i][j].v]);
    }
    int mx = -1;
    for(int i = 0;i<n;i++)
        mx =max(DP[i],mx);
    cout<<mx<<endl;
    return 0;
}