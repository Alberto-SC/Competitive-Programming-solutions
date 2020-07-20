#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<int> state(1000010, 3);
	for (int i = 0; i < 2; ++i) {
		int k;
		cin >> k;
		while (k--) { int v; cin >> v; state[v] &= ~(1<<i); }
	}

	int answer = 0, disl = 0;
	for (int s : state) if (0 == (s&disl)) ++answer, disl = s;
	cout << answer << endl;
}
