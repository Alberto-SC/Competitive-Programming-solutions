#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
struct UnionFind {
	vector<int> par, rank, size;
	int c;
	UnionFind(int n) : par(n), rank(n, 0), size(n, 1), c(n) {
		for(int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }
	void merge(int i, int j) {
		if((i = find(i)) == (j = find(j))) return;
		c--;
		if(rank[i] > rank[j]) swap(i, j);
		par[i] = j;
		size[j] += size[i];
		if(rank[i] == rank[j]) rank[j]++;
	}
};
struct prob {
	double p;
	int r, c;
};
int main() {
	int m, n;
	cin >> m >> n;
	vector<prob> ps;
	ps.reserve(m * n);
	for(int r = 0; r < m; ++r)
		for(int c = 0; c < n; ++c) {
			prob p{0, r, c};
			cin >> p.p;
			ps.push_back(p);
		}
	UnionFind target(m + n), cur(m + n);
	for(int r = 0; r < m; ++r) {
		int k, c;
		cin >> k;
		while(k--) cin >> c, target.merge(r, m + c);
	}
	sort(ps.begin(), ps.end(), [](const prob &l, const prob &r) { return l.p > r.p; });
	vector<prob> ans;
	for(auto &p : ps)
		if(target.same(p.r, m + p.c) && !cur.same(p.r, m + p.c))
			cur.merge(p.r, m + p.c), ans.push_back(p);
	sort(ans.begin(), ans.end(),
	     [](const prob &l, const prob &r) { return tie(l.r, l.c) < tie(r.r, r.c); });
	for(auto &x : ans) cout << x.r << ' ' << x.c << '\n';
	return 0;
}
