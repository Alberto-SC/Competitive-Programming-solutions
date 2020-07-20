#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	// Read input and eliminate duplicates.
	int N;
	cin >> N;
	vector<int> A;
	for (int i = 0, last = -1, a; i < N; ++i) {
		cin >> a;
		if (a != last)
			A.push_back(a);
		last = a;
	}
	N = (int)A.size();

	// Normalize to [0, 1, 2, ...). Also create a mapping i -> instances of i.
	vector<vector<int>> pos;
	int K;
	{
		map<int, int> id;
		for (int a : A) id[a] = 0;
		K = 0;
		for (auto &pr : id) pr.second = K++;
		pos.assign(K, vector<int>());
		for (int i = 0; i < N; ++i) {
			A[i] = id[A[i]];
			pos[A[i]].push_back(i);
		}
	}

	// DP to find as many non-conflicting (x, x+1) pairs as possible.
	// We keep the two best solutions ending in each x, as (#pairs, index of x).
	// A position 'N' indicates that overlap isn't a problem.
	pair<int, int> best[2] = {{0, N}, {0, N}};
	for (int k = 0; k < K; ++k) {
		pair<int, int> nbest[2] = {best[0], best[1]};
		for (int p : pos[k]) {
			// Can (A[p], A[p+1]) be a pair?
			if (p + 1 == N || A[p] + 1 != A[p + 1])
				continue;

			// Improve to the best solution we don't conflict with.
			pair<int, int> s = {0, N};
			if (best[0].second + 1 != p)
				s = {best[0].first + 1, p};
			else
				s = {best[1].first + 1, p};

			// If there is only one occurrence of k+1 then there will be no conflict
			// with any (k+1, k+2) pairs.
			if (pos[k + 1].size() == 1)
				s.second = N;

			// Update.
			if (s > nbest[0])
				nbest[1] = nbest[0], nbest[0] = s;
			else if (s > nbest[1])
				nbest[1] = s;
		}
		best[0] = nbest[0];
		best[1] = nbest[1];
	}

	cout << (N - 1 - best[0].first) << endl;

	return 0;
}
