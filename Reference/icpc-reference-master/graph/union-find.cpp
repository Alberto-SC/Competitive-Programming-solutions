struct UFind{
	int cont;
	vector<int> pai;
	uFind(int n) :cont{n}, pai(n) {
		FOR(i, n) pai[i] = i;
	}
	int find(int i) {
		return pai[i] = (pai[i]==i)? i : find(pai[i]);
	}
	void merge(int i,int j){
		int a = find(i),b = find(j);
		if(a != b){
			cont--;
			pai[a]=b;
		}
	}
};

// Alternative Union-Find
// int parent[MAXVERTICES];
// void make_set(int x){ parent[x] = x; }
// int find(int x){ return (parent[x] == x)? x : parent[x] = find(parent[x]); }
// int joint(int x, int y){ return parent[find(x)] = find(y); }
