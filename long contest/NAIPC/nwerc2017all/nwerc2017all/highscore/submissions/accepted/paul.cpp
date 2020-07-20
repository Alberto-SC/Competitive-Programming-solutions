#include <bits/stdc++.h>
using namespace std;

const int k = 100;

long long score(long long a, long long b, long long c) {
	return a*a + b*b + c*c + 7*min({a,b,c});
}

int main() {
	int tc; cin >> tc;
	while (tc--) {
		long long a, b, c, d;
		cin >> a >> b >> c >> d;
		if (a < b) swap(a,b);
		if (b < c) swap(b,c);
		if (a < b) swap(a,b);
		assert(a >= b && b >= c);
		
		long long res = 0;
		for (long long da = max(0LL, d-k); da <= d; da++) {
			for (long long db = 0; da+db <= d; db++) {
				long long dc = d-da-db;
				res = max(res, score(a+da,b+db,c+dc));
			}
		}
		cout << res << endl;
	}
}
