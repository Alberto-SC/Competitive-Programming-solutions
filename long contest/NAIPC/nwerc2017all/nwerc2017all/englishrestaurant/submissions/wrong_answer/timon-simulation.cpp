#include <bits/stdc++.h>
#include <chrono>
using namespace std;

using TP = chrono::time_point<chrono::high_resolution_clock>;
TP now() { return chrono::high_resolution_clock::now(); }

int main() {
	auto start = now();

	int n, g, t;
	cin >> n >> g >> t;
	vector<int> c(n);
	for (int &v : c) cin >> v;
	sort(c.begin(), c.end());

	long long sum = 0LL, count = 0LL;
	while (chrono::duration_cast<chrono::microseconds>(now()-start).count()
			< 1.9e6) {
		set<int> r(c.begin(), c.end());
		for (int i = 0; i < t; ++i) {
			int sz = 1 + rand() % g;
			auto it = r.lower_bound(sz);
			if (it == r.end()) continue;
			r.erase(it);
			sum += sz;
		}
		count++;
	}

	printf("%.12lf\n", double(sum) / count);

	return 0;
}
