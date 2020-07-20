#define nv second   
#define cp first.second
#define vv first.first
#define nv second.first   
#define cp first.second
#define vv first.first
#define oo 1000000000
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

int level[1000005];
int v[1000005];
int maxflow;
vector<pair<pair<int,int>, int> > adj[100005];

void add_edge(int v, int u, int cap){
	adj[v].pb(mp(mp(u,cap),adj[u].size()));
	adj[u].pb(mp(mp(v,0),adj[v].size()-1));
}

int bfs(int s,int t){
	queue<int> q;
	int v;
	int i;
	level[s] = 0;
	q.push(s);

	while(!q.empty()){
		v = q.front();
		q.pop();

		for(i = 0; i < adj[v].size(); i++){
			if(level[adj[v][i].vv] == -1 && adj[v][i].cp > 0){
				q.push(adj[v][i].vv);
				level[adj[v][i].vv] = level[v] + 1;
			}
		}
	}

	return level[t] == -1;
}

int dfs(int x, int t, int flow){
	if(x == t) return flow;

	for(; v[x] < adj[x].size(); v[x]++){
		pair<pair<int,int>, int> at = adj[x][v[x]];
		
		if(level[at.vv] == level[x] + 1 && at.cp > 0){
			int currflow = min(flow,at.cp);
			currflow = dfs(at.vv, t, currflow);

			if(currflow){
				at.cp -= currflow;
				adj[at.vv][at.nv].cp += currflow;

				adj[x][v[x]] = at;
				return currflow;
			}
		}
	}

	return 0;
}

void dinic(int s,int t){
	while(1){
		memset(level, -1, sizeof level);
		if(bfs(s,t)) break;

		memset(v, 0, sizeof v);
		while(int temp = dfs(s,t,oo)) maxflow += temp;
	}
}
