#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll, ll>;

ll nxt(ll p, ii pr) {
	p -= pr.first;
	p += pr.second - 1;
	return p / pr.second * pr.second;
}

int main() {
	int n;
	cin >> n;

	
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	size_t tower_size = 0;
	{
		unordered_map<ll, unordered_map<ll, int>> froghelper;
		for (int i = 0; i < n; ++i) {
			ll x, d;
			cin >> x >> d;
			pq.push({x, d});
			froghelper[d][x%d]++;
		}
		for (const auto &pr : froghelper) {
			size_t largest = 0;
			for (const auto &pr2 : pr.second)
				largest = max(largest, (size_t)pr2.second);
			tower_size += largest;
		}
	}

	// Keep jumping until we collect enough froggies.
	ii froggies[50];
	while (true) {
		size_t c = 0;
		froggies[c++] = pq.top(), pq.pop();
		while (!pq.empty() && pq.top().first == froggies[0].first)
			froggies[c++] = pq.top(), pq.pop();

		if (c == tower_size) {
			cout << froggies[0].first << ' ' << tower_size << endl;
			break;
		}

		for (size_t i = 0; i < c; ++i)
			froggies[i].first += nxt(pq.top().first, froggies[i]),
			pq.push(froggies[i]);
	}

	return 0;
}
