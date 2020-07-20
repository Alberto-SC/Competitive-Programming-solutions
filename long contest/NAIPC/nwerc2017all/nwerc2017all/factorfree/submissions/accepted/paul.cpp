#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 10;
int a[N], pf[N], res[N];
vector<int> occ[N]; // occ[p] = list of i such that p divides a[i]

bool coprime_with_range(int i, int lo, int hi) {
	for (int b = a[i]; b > 1; ) {
		int p = pf[b];
		auto &v = occ[p];

		auto it = lower_bound(begin(v),end(v),i);
		if (it != begin(v) && *prev(it) >= lo) return false;
		if (next(it) != end(v) && *next(it) <= hi) return false;

		while (b % p == 0) b /= p;
	}
	return true;
}

bool rec(int lo, int hi, int parent = -1) {
	if (lo > hi) return true;
	
	int mid = -1;
	for (int i = lo, j = hi; i <= j; i++, j--) {
		if (coprime_with_range(i,lo,hi)) { mid = i; break; }
		if (coprime_with_range(j,lo,hi)) { mid = j; break; }
	}

	if (mid == -1) return false;
	res[mid] = parent;
	return rec(lo,mid-1,mid) && rec(mid+1,hi,mid);
}

int main() {
	// sieve for prime factors
	iota(pf,pf+N,0);
	for (int i = 2; i < N; i++) if (pf[i] == i)
		for (int j = i+i; j < N; j += i) pf[j] = min(pf[j],i);
	
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		for (int b = a[i]; b > 1; ) {
			int p = pf[b];
			occ[p].push_back(i);
			while (b % p == 0) b /= p;
		}
	}
	
	if (rec(0,n-1)) for (int i = 0; i < n; i++) cout << res[i]+1 << " \n"[i+1 == n];
	else cout << "impossible" << endl;
}
