#include <bits/stdc++.h>
using namespace std;
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(0);

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vector<vi> ady;
vi visited;
vii p;
vector<vii> componentes;

void dfs(vii &comp, int u) {
	visited[u] = true;
	comp.push_back(p[u]);
	for (int v : ady[u]) {
		if (!visited[v])
			dfs(comp, v);
	}
}

int main() {
	optimizar_io
	int n, m, u, v;

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> u;
		p.push_back(ii(u, i));
	}
	ady.assign(n, vi());
	while (m--) {
		cin >> u >> v;
		u--; v--;
		ady[u].push_back(v);
	}
	visited.assign(n, 0);
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			vii comp;
			dfs(comp, i);
			componentes.push_back(comp);
		}
	}
	vector<int> ans(n);
	for (int i = 0; i < componentes.size(); i++) {
		vector<int> idx(componentes[i].size()), val(componentes[i].size());
		for (int j = 0; j < componentes[i].size(); j++) {
			val[j] = componentes[i][j].first;
			idx[j] = componentes[i][j].second;
		}
		sort(val.begin(), val.end(), greater<int>());
		for (int j = 0; j < componentes[i].size(); j++) {
			ans[idx[j]] = val[j];
		}
	}
	for (int a : ans)
		cout << a << " ";
	cout << "\n";
	return 0;
}