#define wt second.second
#define nv second.first   
#define cp first.second
#define vv first.first
#define OO 1000000000000000000
#define oo 1000000000
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

long long level[1000005];
int v[1000005];
int vis[1000005];
vector<pair<pair<int,int>, pair<int,int> > > adj[1000005];
int maxflow;
long long mincost;
int ed;

void add_edge(int v, int u, int cap, int pes){
	adj[v].pb(mp(mp(u, cap), mp(adj[u].size(), pes)));
	adj[u].pb(mp(mp(v, 0), mp(adj[v].size()-1, -pes)));
}

int dij(int s, int t){
	priority_queue<pair<long long, int> > q;
	level[s] = 0;
	q.push(mp(0,s));

	while(!q.empty()){
		long long p = -q.top().ff;
		int v = q.top().ss;
		q.pop();

		for(int i = 0; i < adj[v].size(); i++){
			if(level[adj[v][i].vv] > level[v] + adj[v][i].wt && adj[v][i].cp > 0){
				level[adj[v][i].vv] = level[v] + adj[v][i].wt;
				q.push(mp(-level[adj[v][i].vv],adj[v][i].vv));
			}
		}
	}

	return level[t] == OO;
}

pair<int,long long> dfs(int x, int t, int flow){
	if(vis[x]) return mp(0,0);
	if(x == t) return mp(flow,0);
 	vis[x] = 1;

	for(; v[x] < adj[x].size(); v[x]++){
		pair<pair<int,int>, pair<int,int> > at = adj[x][v[x]];
		
		if(level[at.vv] >= level[x] + at.wt && at.cp > 0){
			pair<int, long long> currflow;
			currflow.ff = min(flow,at.cp);
			currflow = dfs(at.vv, t, currflow.ff);
			currflow.ss += at.wt;
			if(currflow.ff){
				adj[x][v[x]].cp -= currflow.ff;
				adj[at.vv][at.nv].cp += currflow.ff;

				vis[x] = 0;
				return currflow;
			}
		}
	}
	vis[x] = 0;	
	return mp(0,0);
}

void dinic(int s,int t){
	while(1){
		for(int i = 0; i <= ed; i++) level[i] = OO;
		if(dij(s,t)) break;

		memset(v, 0, sizeof v);
		
		pair<int,long long> temp;
		temp = dfs(s,t,oo);
		if(!temp.ff) break;
		maxflow += temp.ff;
		mincost += temp.ss;
	}
}
