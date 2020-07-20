#include <iostream>
using namespace std;

const long long mod = 1e9 + 7;

int main() {
	int n;
	cin >> n;
	long long r = 1;
	bool domod  = false;
	while(n--) {
		long long use;
		cin >> use;

		if(domod || r >= (1ll << 60)) {
			domod = true;
			r     = (2 * r - use) % mod;
		} else {
			r *= 2;
			if(use <= r)
				r -= use;
			else {
				cout << "error\n";
				return 0;
			}
		}
	}
	cout << (r + mod) % mod << endl;
	return 0;
}
