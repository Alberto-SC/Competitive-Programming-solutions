#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
struct Edge{
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    N+=7;
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }
    // cout<<"HI"<<endl;
    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        // cout<<"Shortest Path "<<d[t]<<endl;
        if (d[t] == INF)
            break;
        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }
        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return cost;
}
int main(){
    int n,q,t,l,r,v;
    cin>>n>>q;
    vector<pair<int,int>> pos(n,{1,n});
    vector<Edge> edges;
    for(int i = 0;i<q;i++){
        cin>>t>>l>>r>>v;
        l--,r--;
        if(t == 1)
            for(int j = l;j<=r;j++)
                pos[j].x =max(pos[j].x,v);                
        
        else 
            for(int j = l;j<=r;j++)
                pos[j].y = min(pos[j].y,v);                
        
    }
    // for(int i = 0;i<n;i++)cout<<"("<<pos[i].x<<","<<pos[i].y<<")  ";
    // cout<<endl;
    for(int i = 0;i<n;i++){
        if(pos[i].x>pos[i].y)return cout<<-1<<endl,0;
        edges.push_back({0,i+1,1,0});
        for(int j = pos[i].x ;j<=pos[i].y;j++){
            // cout<<i+1<<" "<<n+1+(j-1)<<endl;
            edges.push_back({i+1,n+1+(j-1),1,0});
        }
        // cout<<endl;
    }
    int idx = (2*n)+1;
    int idx2 = idx;
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            edges.push_back({n+1+i,idx++,1,((j+1)*2)-1});
    for(int i = idx2;i<idx;i++)
        edges.push_back({i,idx,1,0});
    // cout<<idx<<" "<<idx2<<endl;
    cout<<min_cost_flow(idx,edges,n,0,idx)<<endl;
    return 0;
}