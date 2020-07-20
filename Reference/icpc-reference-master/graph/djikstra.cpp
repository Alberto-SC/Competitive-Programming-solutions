vector<int> dist; // answer -> dist[destiny]
vector<vector<ii>> g; // u w v

void djikstra(int src = 1) { 
    dist.resize(g.size(), oo);
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.pb({dist[src] = 0, src});
    while(not pq.empty()) {
        auto c = pq.top(); pq.pop();
        for(auto e : g[c.ss])
            if(dist[e.ss] > c.ff + e.ff)
                pq.pb({dist[e.ss] = c.ff + e.ff, e.ss});
    }
}