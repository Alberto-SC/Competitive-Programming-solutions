#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll b = 1LL, bm = 1LL;
	
	int n;
	cin >> n;
	while (n--) {
		ll bi;
		cin >> bi;
		bm = (((bm * 2LL - bi) % MOD) + MOD) % MOD;

		if (b >= 0LL) {
			b *= 2LL;
			if (b > (1LL << 61)) b = -1LL;
		}
		if (b >= 0LL) {
			b -= bi;
			if (b < 0LL) {
				cout << "error" << endl;
				return 0;
			}
		}
	}
	cout << bm << endl;
}
