#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

// Returns a mapping i \mapsto smallest prime factor of i, for i upto N.
// Modified sieve of Eratosthenes.
vi find_spf(int N) {
	vi spf(N+1, 1);
	for (int i = 2; i <= N; ++i) {
		if (spf[i] > 1) continue;
		spf[i] = i;
		if (i <= N / i)
			for (int j = i * i; j <= N; j += i)
				if (spf[j] == 1)
					spf[j] = i;
	}
	return spf;
}

// Recursively solves range [l, r]. O(n^2)
bool solve(int l, int r, int p, vi &L, vi &R, vi &sol) {
	if (l > r) return true;
	int root = -1;
	for (int i = l; i <= r && root < 0; ++i) {
		if (L[i] < l && R[i] > r) root = i;
	}
	if (root == -1) return false;
	sol[root] = p;
	return solve(l, root-1, root, L, R, sol)
		&& solve(root+1, r, root, L, R, sol);
}

constexpr int UB = 10000010;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	// Precompute smallest prime factors.
	vi spf = find_spf(UB);

	// Read input, and find unique prime factors of each number.
	int n;
	cin >> n;
	vector<unordered_set<int>> af(n, unordered_set<int>());
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		while (a > 1) af[i].insert(spf[a]), a /= spf[a];
	}

	// Find the first number left/right of each number that shares a prime.
	vi L(n, -1), R(n, n), last(UB+1, -1);
	for (int i = 0; i < n; ++i)
		for (int p : af[i])
			L[i] = max(L[i], last[p]),
			last[p] = i;
	last.assign(UB+1, n);
	for (int i = n - 1; i >= 0; --i)
		for (int p : af[i])
			R[i] = min(R[i], last[p]),
			last[p] = i;

	// Recursively solve.
	vi sol(n, -1);
	if (solve(0, n - 1, -1, L, R, sol))
		for (int i = 0; i < n; ++i)
			cout << sol[i] + 1 << " \n"[i + 1 == n];
	else	cout << "impossible\n";

	cout << flush;
	
	return 0;
}
