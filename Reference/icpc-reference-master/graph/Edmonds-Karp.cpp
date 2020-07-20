int bfsek(int s,int t){
	queue<int> q;
	int v;
	int i, vis[305];
	memset(vis,0,sizeof(vis));
	q.push(s);

	while(!q.empty()){
		v = q.front();
		q.pop();
		vis[v] = 1;

		for(i = 0; i < adj[v].size(); i++){
			// Se a capacidade for igual a 0 a aresta nao existe
			if(!vis[adj[v][i]] && cap[v][adj[v][i]] > 0){
				flow[adj[v][i]] = min(cap[v][adj[v][i]],flow[v]);
				q.push(adj[v][i]);
				p[adj[v][i]] = v;
				if(adj[v][i] == t)	return flow[t];
			}
		}
	}
	return 0;
}

int mflow(int s,int t){
	int mi, vai, sai, j;
	int maxflow = 0;

	while(1){
		for(j = 0; j <= 2*(n+1); j++)	flow[j] = oo;

		mi = bfsek(s,t);
		if(mi == 0) break;

		maxflow += mi;
		sai = p[t];
		vai = t;

		// Subtrai o fluxo que passou das arestas utilizadas e soma nas arestas inversas
		while(vai != s){
			cap[sai][vai] -= mi;
			cap[vai][sai] += mi;
			vai = sai;
			sai = p[sai];
		}
	}

	return maxflow;
}
