#include <bits/stdc++.h>
using namespace std;
const int maxn = 500007;
#define x first 
#define y second
#define endl '\n'
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
map<int,int> mp;
vector<pair<int,int>> graph[maxn];
vector<int> bit(maxn,0);
vector<int> depth(maxn);
vector<int> w(maxn);
vector<pair<int,int>> ranges(maxn);
int parent[25][maxn];
void add_edge(int u,int v,int c){
    graph[u].push_back({v,c});
    graph[v].push_back({u,c});
}
vector<int> dist(maxn);
void dfs(int u,int &idx,int p = -1,int d = 0,int dp =0){ 
    ranges[u].x = idx;
    dist[u]  = d;
    depth[u] = dp;
    for(auto v:graph[u]){
        if(v.x == p)continue;
        dfs(v.x,++idx,u,d^v.y,dp+1);
    }
    ranges[u].y = idx;
}

int sum(int idx) {
    int ret = 0;
    for (++idx; idx > 0; idx -= idx&-idx)ret ^= bit[idx];
    return ret;
}

void add(int idx, int delta) {
    for (++idx; idx<maxn;idx += idx&-idx) bit[idx] ^= delta;
}

int add_range(int l,int r,int val){
    add(l, val);
    add(r + 1, -val);
}

void printbit(){
    for(int i = 0;i<4;i++)cout<<(sum(i)^sum(i-1))<<" ";
    cout<<endl;
}
int main(){
    int n,u,v,q,tp,z,c,val,idx = 0;
    cin>>n;
    vector<pair<int,int>> edges(n-1);
    vector<int> cost(n-1);
    for(int i = 0;i<n-1;i++){
        cin>>u>>v>>c;
        u--,v--;
        cost[i] = c&1;
        edges[i] = {u,v};
        add_edge(u,v,c&1);
    }
    dfs(0,idx);
    for(int i = 0;i<n-1;i++){
        u = edges[i].x;
        v = edges[i].y;
        if(depth[u]<depth[v])swap(u,v);
        add(ranges[u].x,cost[i]);
        add(ranges[u].y+1,cost[i]);
    }
    cin>>q;
    for(int i= 0;i<q;i++){
        cin>>tp;
        if(tp == 1){ 
            cin>>u>>v;
            u--,v--;
            int x =sum(ranges[u].x)^sum(ranges[v].x);
            if(x)cout<<"WE NEED BLACK PANDA"<<endl;
            else cout<<"JAKANDA FOREVER"<<endl;
        }
        else{
            cin>>idx>>val;
            idx--;
            val&=1;
            u = edges[idx].x;
            v = edges[idx].y;
            if(depth[u]<depth[v])swap(u,v);
            add_range(ranges[u].x,ranges[u].y,val^cost[idx]);
            cost[idx] = val;
        }
    }
    return 0;
}

