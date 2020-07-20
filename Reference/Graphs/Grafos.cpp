#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
int inf = 1 << 30;
struct disjointSet{
	int N;
	vector<short int> rank;
	vi parent, count;
	disjointSet(int N): N(N), parent(N), count(N), rank(N){}
	void makeSet(int v){
		count[v] = 1;
		parent[v] = v;
	}
	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}
	void unionSet(int a, int b){
		a = findSet(a), b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
			count[b] += count[a];
		}else{
			parent[b] = a;
			count[a] += count[b];
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};

struct edge{
	int source, dest, cost;
	edge(): source(0), dest(0), cost(0){}
	edge(int dest, int cost): dest(dest), cost(cost){}
	edge(int source, int dest, int cost): source(source), dest(dest), cost(cost){}
	bool operator==(const edge & b) const{
		return source == b.source && dest == b.dest && cost == b.cost;
	}
	bool operator<(const edge & b) const{
		return cost < b.cost;
	}
	bool operator>(const edge & b) const{
		return cost > b.cost;
	}
};



struct path{
	int cost = inf;
	vector<int> vertices;
	int size = 1;
	int previous = -1;
};
struct graph{
	vector<vector<edge>> adjList;
	vector<vb> adjMatrix;
	vector<vi> costMatrix;
	vector<edge> edges;
	int V = 0;
	bool dir = false;
	graph(int n, bool dir): V(n), dir(dir), adjList(n), edges(n), adjMatrix(n, vb(n)), costMatrix(n, vi(n)){
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				costMatrix[i][j] = (i == j ? 0 : inf);
	}
	void add(int source, int dest, int cost){
		adjList[source].emplace_back(source, dest, cost);
		edges.emplace_back(source, dest, cost);
		adjMatrix[source][dest] = true;
		costMatrix[source][dest] = cost;
		if(!dir){
			adjList[dest].emplace_back(dest, source, cost);
			adjMatrix[dest][source] = true;
			costMatrix[dest][source] = cost;
		}
	}
	void buildPaths(vector<path> & paths){
		for(int i = 0; i < V; i++){
			int actual = i;
			for(int j = 0; j < paths[i].size; j++){
				paths[i].vertices.push_back(actual);
				actual = paths[actual].previous;
			}
			reverse(paths[i].vertices.begin(), paths[i].vertices.end());
		}
	}
	vector<path> dijkstra(int start){
		priority_queue<edge, vector<edge>, greater<edge>> cola;
		vector<path> paths(V, path());
		vb relaxed(V);
		cola.push(edge(start, 0));
		paths[start].cost = 0;
		while(!cola.empty()){
			int u = cola.top().dest; cola.pop();
			relaxed[u] = true;
			for(edge & current : adjList[u]){
				int v = current.dest;
				if(relaxed[v]) continue;
				int nuevo = paths[u].cost + current.cost;
				if(nuevo == paths[v].cost && paths[u].size + 1 < paths[v].size){
					paths[v].previous = u;
					paths[v].size = paths[u].size + 1;
				}else if(nuevo < paths[v].cost){
					paths[v].previous = u;
					paths[v].size = paths[u].size + 1;
					cola.push(edge(v, nuevo));
					paths[v].cost = nuevo;
				}
			}
		}
		buildPaths(paths);
		return paths;
	}
	vector<path> bellmanFord(int start){
		vector<path> paths(V, path());
		vi processed(V);
		vb inQueue(V);
		queue<int> Q;
		paths[start].cost = 0;
		Q.push(start);
		while(!Q.empty()){
			int u = Q.front(); Q.pop(); inQueue[u] = false;
			if(paths[u].cost == inf) continue;
			++processed[u];
			if(processed[u] == V){
				cout << "Negative cycle\n";
				return {};
			}
			for(edge & current : adjList[u]){
				int v = current.dest;
				int nuevo = paths[u].cost + current.cost;
				if(nuevo == paths[v].cost && paths[u].size + 1 < paths[v].size){
					paths[v].previous = u;
					paths[v].size = paths[u].size + 1;
				}else if(nuevo < paths[v].cost){
					if(!inQueue[v]){
						Q.push(v);
						inQueue[v] = true;
					}
					paths[v].previous = u;
					paths[v].size = paths[u].size + 1;
					paths[v].cost = nuevo;
				}
			}
		}
		buildPaths(paths);
		return paths;
	}
	vector<vi> floyd(){
		vector<vi> tmp = costMatrix;
		for(int k = 0; k < V; ++k)
			for(int i = 0; i < V; ++i)
				for(int j = 0; j < V; ++j)
					if(tmp[i][k] != inf && tmp[k][j] != inf)
						tmp[i][j] = min(tmp[i][j], tmp[i][k] + tmp[k][j]);
		return tmp;
	}
	vector<vb> transitiveClosure(){
		vector<vb> tmp = adjMatrix;
		for(int k = 0; k < V; ++k)
			for(int i = 0; i < V; ++i)
				for(int j = 0; j < V; ++j)
					tmp[i][j] = tmp[i][j] || (tmp[i][k] && tmp[k][j]);
		return tmp;
	}
	vector<vb> transitiveClosureDFS(){
		vector<vb> tmp(V, vb(V));
		function<void(int, int)> dfs = [&](int start, int u){
			for(edge & current : adjList[u]){
				int v = current.dest;
				if(!tmp[start][v]){
					tmp[start][v] = true;
					dfs(start, v);
				}
			}
		};
		for(int u = 0; u < V; u++)
			dfs(u, u);
		return tmp;
	}
	bool isBipartite(){
		vi side(V, -1);
		queue<int> q;
		for (int st = 0; st < V; ++st){
			if(side[st] != -1) continue;
			q.push(st);
			side[st] = 0;
			while(!q.empty()){
				int u = q.front();
				q.pop();
				for (edge & current : adjList[u]){
					int v = current.dest;
					if(side[v] == -1) {
						side[v] = side[u] ^ 1;
						q.push(v);
					}else{
						if(side[v] == side[u]) return false;
					}
				}
			}
		}
		return true;
	}
	vi topologicalSort(){
		int visited = 0;
		vi order, indegree(V);
		for(auto & node : adjList){
			for(edge & current : node){
				int v = current.dest;
				++indegree[v];
			}
		}
		queue<int> Q;
		for(int i = 0; i < V; ++i){
			if(indegree[i] == 0) Q.push(i);
		}
		while(!Q.empty()){
			int source = Q.front();
			Q.pop();
			order.push_back(source);
			++visited;
			for(edge & current : adjList[source]){
				int v = current.dest;
				--indegree[v];
				if(indegree[v] == 0) Q.push(v);
			}
		}
		if(visited == V) return order;
		else return {};
	}
	bool hasCycle(){
		vi color(V);
		function<bool(int, int)> dfs = [&](int u, int parent){
			color[u] = 1;
			bool ans = false;
			int ret = 0;
			for(edge & current : adjList[u]){
				int v = current.dest;
				if(color[v] == 0)
					ans |= dfs(v, u);
				else if(color[v] == 1 && (dir || v != parent || ret++))
					ans = true;
			}
			color[u] = 2;
			return ans;
		};
		for(int u = 0; u < V; ++u)
			if(color[u] == 0 && dfs(u, -1))
				return true;
		return false;
	}
	pair<vb, vector<edge>> articulationBridges(){
		vi low(V), label(V);
		vb points(V);
		vector<edge> bridges;
		int time = 0;
		function<int(int, int)> dfs = [&](int u, int p){
			label[u] = low[u] = ++time;
			int hijos = 0, ret = 0;
			for(edge & current : adjList[u]){
				int v = current.dest;
				if(v == p && !ret++) continue;
				if(!label[v]){
					++hijos;
					dfs(v, u);
					if(label[u] <= low[v])
						points[u] = true;
					if(label[u] < low[v])
						bridges.push_back(current);
					low[u] = min(low[u], low[v]);
				}
				low[u] = min(low[u], label[v]);
			}
			return hijos;
		};
		for(int u = 0; u < V; ++u)
			if(!label[u])
				points[u] = dfs(u, -1) > 1;
		return make_pair(points, bridges);
	}
	vector<vi> scc(){
		vi low(V), label(V);
		int time = 0;
		vector<vi> ans;
		stack<int> S;
		function<void(int)> dfs = [&](int u){
			label[u] = low[u] = ++time;
			S.push(u);
			for(edge & current : adjList[u]){
				int v = current.dest;
				if(!label[v]) dfs(v);
				low[u] = min(low[u], low[v]);
			}
			if(label[u] == low[u]){
				vi comp;
				while(S.top() != u){
					comp.push_back(S.top());
					low[S.top()] = V + 1;
					S.pop();
				}
				comp.push_back(S.top());
				S.pop();
				ans.push_back(comp);
				low[u] = V + 1;
			}
		};
		for(int u = 0; u < V; ++u)
			if(!label[u]) dfs(u);
		return ans;
	}
	vector<edge> kruskal(){
		sort(edges.begin(), edges.end());
		vector<edge> MST;
		disjointSet DS(V);
		for(int u = 0; u < V; ++u)
			DS.makeSet(u);
		int i = 0;
		while(i < edges.size() && MST.size() < V - 1){
			edge current = edges[i++];
			int u = current.source, v = current.dest;
			if(DS.findSet(u) != DS.findSet(v)){
				MST.push_back(current);
				DS.unionSet(u, v);
			}
		}
		return MST;
	}
	bool tryKuhn(int u, vb & used, vi & left, vi & right){
		if(used[u]) return false;
		used[u] = true;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(right[v] == -1 || tryKuhn(right[v], used, left, right)){
				right[v] = u;
				left[u] = v;
				return true;
			}
		}
		return false;
	}
	bool augmentingPath(int u, vb & used, vi & left, vi & right){
		used[u] = true;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(right[v] == -1){
				right[v] = u;
				left[u] = v;
				return true;
			}
		}
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(!used[right[v]] && augmentingPath(right[v], used, left, right)){
				right[v] = u;
				left[u] = v;
				return true;
			}
		}
		return false;
	}



	//vertices from the left side numbered from 0 to l-1

	//vertices from the right side numbered from 0 to r-1

	//graph[u] represents the left side

	//graph[u][v] represents the right side

	//we can use tryKuhn() or augmentingPath()
	vector<pair<int, int>> maxMatching(int l, int r){
		vi left(l, -1), right(r, -1);
		vb used(l);
		for(int u = 0; u < l; ++u){
			tryKuhn(u, used, left, right);
			fill(used.begin(), used.end(), false);
		}
		vector<pair<int, int>> ans;
		for(int u = 0; u < r; ++u){
			if(right[u] != -1){
				ans.emplace_back(right[u], u);
			}
		}
		return ans;
	}
	void dfs(int u, vi & status, vi & parent){
		status[u] = 1;
		for(edge & current : adjList[u]){
			int v = current.dest;
			if(status[v] == 0){ //not visited
				parent[v] = u;
				dfs(v, status, parent);
			}else if(status[v] == 1){ //explored
				if(v == parent[u]){
					//bidirectional node u<-->v
				}else{
					//back edge u-v 
				}
			}else if(status[v] == 2){ //visited
				//forward edge u-v
			}
		}
		status[u] = 2;
	}
};
struct tree{
	vi parent, level, weight;
	vector<vi> dists, DP;
	int n, root;
	void dfs(int u, graph & G){
		for(edge & curr : G.adjList[u]){
			int v = curr.dest;
			int w = curr.cost;
			if(v != parent[u]){
				parent[v] = u;
				weight[v] = w;
				level[v] = level[u] + 1;
				dfs(v, G);
			}
		}
	}
	tree(int n, int root): n(n), root(root), parent(n), level(n), weight(n), dists(n, vi(20)), DP(n, vi(20)){
		parent[root] = root;
	}
	tree(graph & G, int root): n(G.V), root(root), parent(G.V), level(G.V), weight(G.V), dists(G.V, vi(20)), DP(G.V, vi(20)){
		parent[root] = root;
		dfs(root, G);
	}
	void pre(){
		for(int u = 0; u < n; u++){
			DP[u][0] = parent[u];
			dists[u][0] = weight[u];
		}
		for(int i = 1; (1 << i) <= n; ++i){
			for(int u = 0; u < n; ++u){
				DP[u][i] = DP[DP[u][i - 1]][i - 1];
				dists[u][i] = dists[u][i - 1] + dists[DP[u][i - 1]][i - 1];
			}
		}
	}
	int ancestor(int p, int k){
		int h = level[p] - k;
		if(h < 0) return -1;
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= h){
				p = DP[p][i];
			}
		}
		return p;
	}
	int lca(int p, int q){
		if(level[p] < level[q]) swap(p, q);
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= level[q]){
				p = DP[p][i];
			}
		}
		if(p == q) return p;
		for(int i = lg; i >= 0; --i){
			if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
				p = DP[p][i];
				q = DP[q][i];
			}
		}
		return parent[p];
	}
	int dist(int p, int q){
		if(level[p] < level[q]) swap(p, q);
		int lg;
		for(lg = 1; (1 << lg) <= level[p]; ++lg);
		lg--;
		int sum = 0;
		for(int i = lg; i >= 0; --i){
			if(level[p] - (1 << i) >= level[q]){
				sum += dists[p][i];
				p = DP[p][i];
			}
		}
		if(p == q) return sum;
		for(int i = lg; i >= 0; --i){
			if(DP[p][i] != -1 && DP[p][i] != DP[q][i]){
				sum += dists[p][i] + dists[q][i];
				p = DP[p][i];
				q = DP[q][i];
			}
		}
		sum += dists[p][0] + dists[q][0];
		return sum;
	}

};



template<typename T>
struct flowEdge{
  int dest;
  T flow, capacity, cost;
  flowEdge *res;
  flowEdge(): dest(0), flow(0), capacity(0), cost(0), res(NULL){}
  flowEdge(int dest, T flow, T capacity, T cost = 0): dest(dest), flow(flow), capacity(capacity), cost(cost), res(NULL){}
  void addFlow(T flow){
    this->flow += flow;
    this->res->flow -= flow;
  }
};

template<typename T>
struct flowGraph{
  T inf = numeric_limits<T>::max();
  vector<vector<flowEdge<T>*>> adjList;
  vector<int> dist, pos;
  int V;
  flowGraph(int V): V(V), adjList(V), dist(V), pos(V){}
  ~flowGraph(){
    for(int i = 0; i < V; ++i)
      for(int j = 0; j < adjList[i].size(); ++j)
        delete adjList[i][j];
  }
  void addEdge(int u, int v, T capacity, T cost = 0){
    flowEdge<T> *uv = new flowEdge<T>(v, 0, capacity, cost);
    flowEdge<T> *vu = new flowEdge<T>(u, capacity, capacity, -cost);
    uv->res = vu;
    vu->res = uv;
    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
  }



  //Maximun Flow using Dinic Algorithm O(EV^2)

  T blockingFlow(int u, int t, T flow){
    if(u == t) return flow;
    for(int &i = pos[u]; i < adjList[u].size(); ++i){
      flowEdge<T> *v = adjList[u][i];
      if(v->capacity > v->flow && dist[u] + 1 == dist[v->dest]){
        T fv = blockingFlow(v->dest, t, min(flow, v->capacity - v->flow));
        if(fv > 0){
          v->addFlow(fv);
          return fv;
        }
      }
    }
    return 0;
  }
  T dinic(int s, int t){
    T maxFlow = 0;
    dist[t] = 0;
    while(dist[t] != -1){
      fill(dist.begin(), dist.end(), -1);
      queue<int> Q;
      Q.push(s);
      dist[s] = 0;
      while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(flowEdge<T> *v : adjList[u]){
          if(dist[v->dest] == -1 && v->flow != v->capacity){
            dist[v->dest] = dist[u] + 1;
            Q.push(v->dest);
          }
        }
      }
      if(dist[t] != -1){
        T f;
        fill(pos.begin(), pos.end(), 0);
        while(f = blockingFlow(s, t, inf))
          maxFlow += f;
      }
    }
    return maxFlow;
  }
  //Maximun Flow using Edmonds-Karp Algorithm O(VE^2)
  T edmondsKarp(int s, int t){
    T maxFlow = 0;
    vector<flowEdge<T>*> parent(V);
    while(true){
      fill(parent.begin(), parent.end(), nullptr);
      queue<int> Q;
      Q.push(s);
      while(!Q.empty() && !parent[t]){
        int u = Q.front(); Q.pop();
        for(flowEdge<T> *v : adjList[u]){
          if(!parent[v->dest] && v->capacity > v->flow){
            parent[v->dest] = v;
            Q.push(v->dest);
          }
        }
      }
      if(!parent[t]) break;
      T f = inf;
      for(int u = t; u != s; u = parent[u]->res->dest)
        f = min(f, parent[u]->capacity - parent[u]->flow);
      for(int u = t; u != s; u = parent[u]->res->dest)
        parent[u]->addFlow(f);
      maxFlow += f;
    }
    return maxFlow;
  }

  //Max Flow Min Cost
  pair<T, T> maxFlowMinCost(int s, int t){
    vector<bool> inQueue(V);
    vector<T> distance(V), cap(V);
    vector<flowEdge<T>*> parent(V);
    T maxFlow = 0, minCost = 0;
    while(true){
      fill(distance.begin(), distance.end(), inf);
      fill(parent.begin(), parent.end(), nullptr);
      fill(cap.begin(), cap.end(), 0);
      distance[s] = 0;
      cap[s] = inf;
      queue<int> Q;
      Q.push(s);
      while(!Q.empty()){
        int u = Q.front(); Q.pop(); inQueue[u] = 0;
        for(flowEdge<T> *v : adjList[u]){
          if(v->capacity > v->flow && distance[v->dest] > distance[u] + v->cost){
            distance[v->dest] = distance[u] + v->cost;
            parent[v->dest] = v;
            cap[v->dest] = min(cap[u], v->capacity - v->flow);
            if(!inQueue[v->dest]){
              Q.push(v->dest);
              inQueue[v->dest] = true;
            }
          }
        }
      }
      if(!parent[t]) break;
      maxFlow += cap[t];
      minCost += cap[t] * distance[t];
      for(int u = t; u != s; u = parent[u]->res->dest)
        parent[u]->addFlow(cap[t]);
    }
    return {maxFlow, minCost};
  }
};



//____________________UNION FIND___________________________//
int raiz(int i) {
		while(i != padre[i]) i = padre[i];
		return i;
	}
bool conexos(int u,int v){
    return raiz(u) == raiz(v);
}

void union_find(int u,int v){
    if(conexos(u,v))return;
    u = raiz(u);
    v = raiz(v);
    if(h[u] < h[v])padre[u] = v; 
    else{
        padre[v] = u;
        if(h[u]  == h[v])++h[u];
    }    
}


//_______________________________KRUSKAL_________________________//
long long kruskal(vector<edge> &edges){
	long long cost = 0;
	edge ed;
	sort(edges.begin(),edges.end(),comp);
	int n = edges.size();
    for (int i = n-1; i >=0; i--) {
		ed = edges[i];
		if (!conexos(ed.u, ed.v)) { 
			cost += ed.c;
			union_find(ed.u, ed.v);
		}
	}
	return cost;
}

//_______________SHORTEST CYCLE__________________//*****
// void solve(int v) {
// 	int topQ = 0;
// 	for (int i = 0; i < n; i++)
// 		dist[i] = N;
// 	dist[v] = 0;
// 	q[topQ++] = v;
// 	for (int i = 0; i < topQ; i++) {
// 		v = q[i];
// 		for (int u : graph[v]) {
// 			if (dist[u] == N) {
// 				dist[u] = dist[v] + 1;
// 				q[topQ++] = u;
// 			} else if (dist[u] >= dist[v]) {
// 				ans = min(ans, dist[v] + dist[u] + 1);
// 			}
// 		}
// 	}
// }
void addedge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
void bfs(int root){
    queue<int> q;
    // int best_u,best_v;
    // vector<int> parent(100, -1); 
    vector<int> level(n,-1);
    // vector<bool> vis(100,-1);
    q.push(root);
    level[root] = 0;
    // int min_cycle = INT_MAX;
    while(!q.empty()){
        int u = q.front(); 
        q.pop(); 
        // vis[u] = true;
        // if(level[u]>prune_level)
        //     break;
        for(auto v:graph[u]){
            // if(parent[u] == v)continue;
            if(level[v] == -1){
                level[v] = level[u] +1;
                // parent[v] = u;
                q.push(v);
            }
            else if(level[v]>=level[u]){
                ans= min(ans,level[u] + 1 + level[v]);
                // prune_level = level[v] - 1;
                // int cycle_len = level[u] + 1 + level[v];
                // if(cycle_len<min_cycle){
                //     min_cycle = cycle_len;
                //     best_u = u;
                //     best_v = v;
                // }
            }
        }
    }
}
//___________BFS______________//
/*
	Mark de largest distance form a source to all vertex
*/
int bfs(int diameter,vector<int> graph[],int source,int who){
    vector<int> vis(40007,-1);
    queue<int> Q;
    Q.push(source);
    int u;
    vis[source] = 0;
    while(!Q.empty()){
        u = Q.front();
        Q.pop();
        if(diameter)
            if(who) 
                dis1[u] = max(dis1[u],vis[u]);
            else 
                dis2[u] = max(dis2[u],vis[u]);
        for(auto v:graph[u]){
            if(vis[v] == -1){
                vis[v] = vis[u]+1;
                Q.push(v);
            }
        }
    }
    return u;
}
//______________MAXIMUN MATCHING______//
/*
	KUHN's  
	Whit adjacent matrix
*/
const int MAXN = 1000;
char Mgraph[MAXN][MAXN];
vector<int> vis(MAXN);
vector<int> mark(MAXN);
int match(int nodo,int m){
	int x;
  	if(vis[nodo] == 1) return 0;
  	vis[nodo] = 1;
  	for(x = 0;x <m;x++)
    	if( Mgraph[nodo][x] == 1 && (mark[x] == -1 || match(mark[x])) ){
       	mark[x] = nodo;
       	return 1;
    }
  	return 0;
}
int Aumenting_paths_matrix(int n,int m){
	maxMatxh = 0;
	for(x=1;x<=n;x++){
		vis.assign(n*m,0)
		if(match(x),m) maxMath++;
	}
}
/*
	Hopcroft karp() O(E sqrt(v))
*/
#define MAX 100001
#define NIL 0
#define INF (1<<28)
vector< int > G[MAX];
int n, m, match[MAX], dist[MAX];
bool bfs() {
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) {
        if(match[i]==NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=NIL) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[match[v]]==INF) {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool dfs(int u) {
    int i, v, len;
    if(u!=NIL) {
        len = G[u].size();
        for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[match[v]]==dist[u]+1) {
                if(dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    int matching = 0, i;
    while(bfs())
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i))
                matching++;
    return matching;
}
//______Kuhn's_______//
int n, k;
vector < vector<int> > g;
vector<int> mt;
vector<char> used;
 
bool try_kuhn (int v) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}
int main() {
 
	mt.assign (k, -1);
	vector<char> used1 (n);
	for (int i=0; i<n; ++i)
		for (size_t j=0; j<g[i].size(); ++j)
			if (mt[g[i][j]] == -1) {
				mt[g[i][j]] = i;
				used1[i] = true;
				break;
			}
	for (int i=0; i<n; ++i) {
		if (used1[i])  continue;
		used.assign (n, false);
		try_kuhn (i);
	}
 
	for (int i=0; i<k; ++i)
		if (mt[i] != -1)
			printf ("%d %d\n", mt[i]+1, i+1);
}

/********************************************************************************
    MaxFlow Dinic algorithm with scaling. 
    O(N * M * log(MC)), where MC is maximum edge capacity.
    
    Based on problem 2784 from informatics.mccme.ru 
    http://informatics.mccme.ru/mod/statements/view3.php?chapterid=2784#1
********************************************************************************/
struct edge {
    int a, b, f, c;
};

const int inf = 1000 * 1000 * 1000;
const int MAXN = 1050;

int n, m;
vector <edge> e;
int pt[MAXN]; // very important performance trick
vector <int> g[MAXN];
long long flow = 0;
queue <int> q;
int d[MAXN];
int lim;
int s, t;

void add_edge(int a, int b, int c) {                                                                           
    edge ed;

    //keep edges in vector: e[ind] - direct edge, e[ind ^ 1] - back edge 

    ed.a = a; ed.b = b; ed.f = 0; ed.c = c;
    g[a].push_back(e.size());
    e.push_back(ed);

    ed.a = b; ed.b = a; ed.f = c; ed.c = c;
    g[b].push_back(e.size());
    e.push_back(ed);
}

bool bfs() {
    for (int i = s; i <= t; i++)
        d[i] = inf;
    d[s] = 0; 
    q.push(s);
    while (!q.empty() && d[t] == inf) {
        int cur = q.front(); q.pop();
        for (size_t i = 0; i < g[cur].size(); i++) {
            int id = g[cur][i];
            int to = e[id].b;

            //printf("cur = %d id = %d a = %d b = %d f = %d c = %d\n", cur, id, e[id].a, e[id].b, e[id].f, e[id].c);

            if (d[to] == inf && e[id].c - e[id].f >= lim) {
                d[to] = d[cur] + 1;
                q.push(to);
            }
        }
    }
    while (!q.empty()) 
        q.pop();
    return d[t] != inf;
}

bool dfs(int v, int flow) {
    if (flow == 0) 
        return false;
    if (v == t) {
        //cout << v << endl;
        return true;
    }
    for (; pt[v] < g[v].size(); pt[v]++) {
        int id = g[v][pt[v]];
        int to = e[id].b;

        //printf("v = %d id = %d a = %d b = %d f = %d c = %d\n", v, id, e[id].a, e[id].b, e[id].f, e[id].c);

        if (d[to] == d[v] + 1 && e[id].c - e[id].f >= flow) {
            int pushed = dfs(to, flow); 
            if (pushed) {
                e[id].f += flow;
                e[id ^ 1].f -= flow;
                return true;
            }               
        }
    }
    return false;
}

void dinic() {
    for (lim = (1 << 30); lim >= 1;) {
        if (!bfs()) {
            lim >>= 1;
            continue;
        }

        for (int i = s; i <= t; i++) 
            pt[i] = 0;

        int pushed;

        while (pushed = dfs(s, lim)) { 
            flow = flow + lim;
        }

        //cout << flow << endl;
    }
}

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    scanf("%d %d", &n, &m);
    
    s = 1; t = n;

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a, b, c);
    }

    dinic();

    cout << flow << endl;

    return 0;
}
//______________________Other dinic_____________//
using ll = long long;
using vl = vector<ll>;
#define FOR(i, a, b) for(ll i = (a); i < (b); i++)
#define FORD(i, a, b) for(ll i = (b)-1; i >= (a); i--)
 
typedef vector<int> VI;
typedef vector<VI> VVI;
const ll INF = 1000000000000000000LL;
 
#define VEI(w,e) ((E[e].u == w) ? E[e].v : E[e].u)
#define CAP(w,e) ((E[e].u == w) ? E[e].cap[0] - E[e].flow : E[e].cap[1] + E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))
 
struct Edge { int u, v; ll cap[2], flow; };
 
VI d, act;
 
bool bfs(int s, int t, VVI& adj, vector<Edge>& E, ll lim) {
  queue<int> Q;
  d = VI(adj.size(), -1);
  d[t] = 0;
  Q.push(t);
  while (not Q.empty() and d[s] == -1) {
    int u = Q.front(); Q.pop();
    for (int i = 0; i < int(adj[u].size()); ++i) {
      int e = adj[u][i], v = VEI(u, e);
      if (CAP(v, e) >= lim and d[v] == -1) {
        d[v] = d[u] + 1;
        Q.push(v);
      }
    }
  }
  return d[s] >= 0;
}
 
bool dfs(int u,int t,ll bot,VVI& adj,vector<Edge>& E, ll lim) {
  if (bot == 0) return false;
  if (u == t) return true;
  for (; act[u] < int(adj[u].size()); ++act[u]) {
    int e = adj[u][act[u]];
    if (CAP(u, e) >= lim and d[u] == d[VEI(u, e)] + 1) {
      ll inc=dfs(VEI(u,e),t,min(bot,CAP(u,e)),adj,E,lim);
      if (inc) {
        ADD(u, e, lim);
        return true;
      }
    }
  }
  return false;
}
 
ll maxflow(int s, int t, VVI& adj, vector<Edge>& E) {
  for (int i=0; i<int(E.size()); ++i) E[i].flow = 0;
  ll flow = 0;
  for(int lim = (1<<30); lim >= 1;) {
    if(!bfs(s,t,adj,E, lim)) {
      lim >>= 1;
      continue;
    }
    act = VI(adj.size(), 0);
    while (dfs(s,t,INF, adj, E, lim)) flow += lim;
  }
  return flow;
}
 
void addEdge(int u, int v, VVI& adj, vector<Edge>& E, ll cap){
	Edge e;
	e.u = u;
	e.v = v;
	e.cap[0] = cap;
	e.cap[1] = cap;
	e.flow = 0;
	adj[u].push_back(E.size());
	adj[v].push_back(E.size());
	E.push_back(e);
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>>adj(n);
	vector<Edge> E;
	for(int i = 0; i < m; ++i) {
		int x,y,w;
		cin >> x >> y >> w;
		--x;--y;
		addEdge(x, y, adj, E, w);
	}
	cout << maxflow(0, n-1, adj ,E) << endl;
}
//_________Normal dinic_____//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
#define FOR(i, a, b) for(ll i = (a); i < (b); i++)
#define FORD(i, a, b) for(ll i = (b)-1; i >= (a); i--)
 
typedef vector<int> VI;
typedef vector<VI> VVI;
const ll INF = 1000000000000000000LL;
 
#define VEI(w,e) ((E[e].u == w) ? E[e].v : E[e].u)
#define CAP(w,e) ((E[e].u == w) ? E[e].cap[0] - E[e].flow : E[e].cap[1] + E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))
 
struct Edge { int u, v; ll cap[2], flow; };
 
VI d, act;
 
bool bfs(int s, int t, VVI& adj, vector<Edge>& E) {
  queue<int> Q;
  d = VI(adj.size(), -1);
  d[t] = 0;
  Q.push(t);
  while (not Q.empty()) {
    int u = Q.front(); Q.pop();
    for (int i = 0; i < int(adj[u].size()); ++i) {
      int e = adj[u][i], v = VEI(u, e);
      if (CAP(v, e) > 0 and d[v] == -1) {
        d[v] = d[u] + 1;
        Q.push(v);
      }
    }
  }
  return d[s] >= 0;
}
 
ll dfs(int u,int t,ll bot,VVI& adj,vector<Edge>& E) {
  if (u == t) return bot;
  for (; act[u] < int(adj[u].size()); ++act[u]) {
    int e = adj[u][act[u]];
    if (CAP(u, e) > 0 and d[u] == d[VEI(u, e)] + 1) {
      ll inc=dfs(VEI(u,e),t,min(bot,CAP(u,e)),adj,E);
      if (inc) {
        ADD(u, e, inc);
        return inc;
      }
    }
  }
  return 0;
}
 
ll maxflow(int s, int t, VVI& adj, vector<Edge>& E) {
  for (int i=0; i<int(E.size()); ++i) E[i].flow = 0;
  ll flow = 0, bot;
  while (bfs(s, t, adj, E)) {
    act = VI(adj.size(), 0);
    while ((bot = dfs(s,t,INF, adj, E))) flow += bot;
  }
  return flow;
}
 
void addEdge(int u, int v, VVI& adj, vector<Edge>& E, ll cap){
	Edge e;
	e.u = u;
	e.v = v;
	e.cap[0] = cap;
	e.cap[1] = cap;
	e.flow = 0;
	adj[u].push_back(E.size());
	adj[v].push_back(E.size());
	E.push_back(e);
}
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>>adj(n);
	vector<Edge> E;
	for(int i = 0; i < m; ++i) {
		int x,y,w;
		cin >> x >> y >> w;
		--x;--y;
		addEdge(x, y, adj, E, w);
	}
	cout << maxflow(0, n-1, adj ,E) << endl;
}
//________DINIC______//
const int MAXN = ...; // число вершин
const int INF = 1000000000; // константа-бесконечность
 
struct edge {
	int a, b, cap, flow;
};
 
int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<int> g[MAXN];
 
void add_edge (int a, int b, int cap) {
	edge e1 = { a, b, cap, 0 };
	edge e2 = { b, a, 0, 0 };
	g[a].push_back ((int) e.size());
	e.push_back (e1);
	g[b].push_back ((int) e.size());
	e.push_back (e2);
}
 
bool bfs() {
	int qh=0, qt=0;
	q[qt++] = s;
	memset (d, -1, n * sizeof d[0]);
	d[s] = 0;
	while (qh < qt && d[t] == -1) {
		int v = q[qh++];
		for (size_t i=0; i<g[v].size(); ++i) {
			int id = g[v][i],
				to = e[id].b;
			if (d[to] == -1 && e[id].flow < e[id].cap) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
		}
	}
	return d[t] != -1;
}
 
int dfs (int v, int flow) {
	if (!flow)  return 0;
	if (v == t)  return flow;
	for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
		int id = g[v][ptr[v]],
			to = e[id].b;
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
		if (pushed) {
			e[id].flow += pushed;
			e[id^1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}
 
int dinic() {
	int flow = 0;
	for (;;) {
		if (!bfs())  break;
		memset (ptr, 0, n * sizeof ptr[0]);
		while (int pushed = dfs (s, INF))
			flow += pushed;
	}
	return flow;
}
//_____DINIC IN MATRIX___//
const int MAXN = ...; // число вершин
const int INF = 1000000000; // константа-бесконечность
 
int n, c[MAXN][MAXN], f[MAXN][MAXN], s, t, d[MAXN], ptr[MAXN], q[MAXN];
 
bool bfs() {
	int qh=0, qt=0;
	q[qt++] = s;
	memset (d, -1, n * sizeof d[0]);
	d[s] = 0;
	while (qh < qt) {
		int v = q[qh++];
		for (int to=0; to<n; ++to)
			if (d[to] == -1 && f[v][to] < c[v][to]) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
	}
	return d[t] != -1;
}
 
int dfs (int v, int flow) {
	if (!flow)  return 0;
	if (v == t)  return flow;
	for (int & to=ptr[v]; to<n; ++to) {
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs (to, min (flow, c[v][to] - f[v][to]));
		if (pushed) {
			f[v][to] += pushed;
			f[to][v] -= pushed;
			return pushed;
		}
	}
	return 0;
}
 
int dinic() {
	int flow = 0;
	for (;;) {
		if (!bfs())  break;
		memset (ptr, 0, n * sizeof ptr[0]);
		while (int pushed = dfs (s, INF))
			flow += pushed;
	}
	return flow;
}
//_________Edmonds-Karp algorithm________//
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
// Count numbre of nodes in subtree whit root v
void dfs_size(int v, int p) {
	sz[v] = 1;
	for (auto u : adj[v]) {
		if (u != p) {
			dfs_size(u, v);
			sz[v] += sz[u];
		}
	}
}