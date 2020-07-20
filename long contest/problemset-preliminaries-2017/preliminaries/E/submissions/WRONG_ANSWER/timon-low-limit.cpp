#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<ll>;

constexpr int B = 60;

int main() {
	ll N;
	int K;
	cin >> N >> K;
	
	vi bits(B, 0);
	int sofar = 0, zero = 1;
	for (int i = B-1; i >= 0; --i) {
		bits[i] = (N>>i)&zero;
		if (!bits[i]) continue;
		sofar++;
		if (sofar == K) {
			bits[i] = zero = 0;
			--sofar;
			for (int j = i + 1; j < B; ++j) {
				bits[j] = !bits[j];
				sofar += bits[j] ? 1 : -1;
				if (bits[j]) break;
			}
		}
	}
	
	ll ans = 0LL;
	for (int i = 0; i < B; ++i) {
		if (sofar < K && !bits[i]) bits[i] = 1, ++sofar;
		ans |= bits[i] << i;
	}
	cout << ans << endl;
	
	return 0;
}
