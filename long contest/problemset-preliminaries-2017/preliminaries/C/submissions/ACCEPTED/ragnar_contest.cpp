#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
struct edge {
	int u, v, c, i;
};
struct PQ {
	int d;
	int v;
};
bool operator<(const PQ &l, const PQ &r) { return l.d < r.d; }
void dijkstra(vector<vector<edge>> &edges, int s, int t, set<int> &vs, set<int> &es) {
	vector<int> dist(edges.size(), 0);
	vector<pair<int, int>> p(edges.size(), {-1, -1});
	priority_queue<PQ, vector<PQ>> pq;
	dist[s] = 1e9;
	pq.push({int(1e9), s});
	while(!pq.empty()) {
		auto d = pq.top().d;
		auto u = pq.top().v;
		pq.pop();
		if(u == t) goto end;
		if(d == dist[u])
			for(auto &e : edges[u])
				if(dist[e.v] < min(d, e.c))
					pq.push({dist[e.v] = min(d, e.c), e.v}), p[e.v] = {u, e.i};
	}
	assert(false);
end:;
	int u = t;
	vs.insert(u);
	while(p[u].first != -1) {
		vs.insert(p[u].first);
		es.insert(p[u].second);
		u = p[u].first;
	}
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<edge>> g(n);
	for(int i = 0; i < m; ++i) {
		edge e;
		cin >> e.u >> e.v >> e.c;
		e.i = i;
		// --e.u, --e.v; // problem is now 0-based
		g[e.u].push_back(e);
		swap(e.u, e.v);
		g[e.u].push_back(e);
	}
	set<int> vs, es, remove;
	dijkstra(g, 0, n - 1, vs, es);
	for(auto &v : vs)
		for(auto &e : g[v]) remove.insert(e.i);
	vector<int> diff;
	set_difference(remove.begin(), remove.end(), es.begin(), es.end(),
	               inserter(diff, diff.begin()));
	if(diff.size() == 0)
		cout << "none\n";
	else
		for(size_t i = 0; i < diff.size(); ++i) cout << diff[i] << " \n"[i == diff.size() - 1];
	return 0;
}
