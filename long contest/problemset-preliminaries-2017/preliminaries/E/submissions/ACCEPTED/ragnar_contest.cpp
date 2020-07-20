#include <cassert>
#include <iostream>
using namespace std;

int main() {
	long long n, k;
	cin >> n >> k;
	// omit ll for WA
	long long c = __builtin_popcountll(n);
	if(c < k) {
		// keep adding bits on the right till k bits
		long long b = 1;
		while(c < k) {
			if((n & b) == 0) {
				n ^= b;
				++c;
			}
			b <<= 1;
		}
	} else { // c >= k
		// find kth bit from the left, double that one
		// add extra bits from the right
		while(c > k) {
			// last bit
			long long b = n & (-n);
			n ^= b;
			--c;
		}
		long long b = n & (-n);
		n += b;
		c = __builtin_popcountll(n);
		assert(c <= k);
		auto remaining = k - c;
		n += (1ll << remaining) - 1;
	}
	cout << n << endl;
	return 0;
}
