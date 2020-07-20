#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ld = long double;

// UF
struct UnionFind {
	vi par, rank, size; int c;
	UnionFind(int n) : par(n), rank(n,0), size(n,1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}

	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	int get_size(int i) { return size[find(i)]; }
	int count() { return c; }

	void merge(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};
//-UF

struct e { int r, c; };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int R, C;
	cin >> R >> C;

	vector<vector<ld>> P(R, vector<ld>(C, 0.0));
	for (auto &row : P) for (ld &p : row) cin >> p;

	vector<e> v;
	for (int r = 0, k, c; r < R; ++r) {
		cin >> k;
		while (k--) cin >> c, v.push_back({r, c});
	}

	sort(v.begin(), v.end(), [&P](const e &l, const e &r) {
		return P[l.r][l.c] > P[r.r][r.c];
	});

	UnionFind uf(R + C);		
	vector<e> ans;
	for (const e &w : v)
		if (!uf.same(w.r, R+w.c))
			ans.push_back(e(w)),
			uf.merge(w.r, R+w.c);

	sort(ans.begin(), ans.end(), [](const e &l, const e &r) {
		return l.r != r.r ? l.r < r.r : l.c < r.c;
	});

	for (const e &w : ans)
		cout << w.r << ' ' << w.c << '\n';
}
