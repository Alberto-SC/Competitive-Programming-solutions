#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<ll, ll>;

// CRT
ll mod(ll a, ll b) { return ((a % b) + b) % b; }

// Finds x, y s.t. ax + by = d = gcd(a, b).
void extended_euclid(ll a, ll b, ll &x, ll &y, ll &d) {
	ll xx = y = 0;
	ll yy = x = 1;
	while (b) {
		ll q = a / b;
		ll t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	d = a;
}

// Solves x = a1 mod m1, x = a2 mod m2, x is unique modulo lcm(m1, m2).
// Returns {0, -1} on failure, {x, lcm(m1, m2)} otherwise.
pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2) {
	ll s, t, d;
	extended_euclid(m1, m2, s, t, d);
	if (a1 % d != a2 % d) return {0, -1};
	return {mod(s*a2 %m2 * m1 + t*a1 %m1 * m2, m1 * m2) / d, m1 / d * m2};
}
//-CRT

ii align(ii pos, ii other) {
	ll jump = pos.second;
	pos.first += max(0LL, (other.first - pos.first + jump - 1)) / jump * jump;
	return pos;
}

void recurse(map<ll, vector<ll>>::iterator it, ii cur,
		map<ll, vector<ll>> &frogs, ii &best) {
	if (it == frogs.end()) {
		if (cur < best) best = cur;
		return;
	}
	ll jump = it->first;
	vector<ll> &froggies = it->second;
	it++;
	
	// Collect the frogs in groups with the same position (mod jumping
	// distance).
	for (size_t l = 0, r = 0; l < froggies.size(); l = r) {
		while (r < froggies.size() && froggies[l] % jump == froggies[r] % jump)
			++r;
		
		// Frogs in [l, r) have the same position % jump, so they go together.
		ii nxt = crt(cur.first, cur.second, froggies[l], jump);
		if (nxt.second < 0LL) continue; // This shouldn't happen :)))))

		// Make sure we don't jump to the left.
		nxt = align(nxt, cur);
		for (size_t i = l; i < r; ++i) nxt = align(nxt, {froggies[i], jump});

		recurse(it, nxt, frogs, best);
	}
}

int main() {
	int n;
	cin >> n;

	map<ll, vector<ll>> frogs;
	for (int i = 0; i < n; ++i) {
		ll x, d;
		cin >> x >> d;
		frogs[d].push_back(x);
	}

	for (auto &f : frogs)
		sort(f.second.begin(), f.second.end(),
			[&f](const ll &l, const ll &r) {
				return l % f.first < r % f.first;
			});

	ii best = {ll(1e18), ll(1e18)};
	recurse(frogs.begin(), {0LL, 1LL}, frogs, best);
	cout << best.first << ' ' << frogs.size() << endl;

	return 0;
}
