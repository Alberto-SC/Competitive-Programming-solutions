#include <bits/stdc++.h>
using namespace std;

int main() {
	long long N, k;
	cin >> N >> k;
	do { ++N; } while (__builtin_popcount(N) != k);
	cout << N << endl;
	return 0;
}
