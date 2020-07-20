#include <bits/stdc++.h>
using namespace std;

int main() {
	int tc; cin >> tc;
	while (tc--) {
		unsigned int x; cin >> x;
		if (!x) cout << '0';
		deque<int> v;
		for (; x; x /= 3) v.push_front(x % 3);
		for (int d: v) cout << d;
		cout << '\n';
	}
}
