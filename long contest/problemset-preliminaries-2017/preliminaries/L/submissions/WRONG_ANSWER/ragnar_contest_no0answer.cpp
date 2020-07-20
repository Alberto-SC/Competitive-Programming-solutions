#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = long long;
using ii = pair<ll, ll>;
ll mod(ll a, ll b) { return ((a % b) + b) % b; }
ll mulmod2(ll a, ll b, ll m) { return __int128(a) * b % m; }
// Finds x, y s.t. ax + by = d = gcd(a, b).
void extended_euclid(ll a, ll b, ll &x, ll &y, ll &d) {
	ll xx = y = 0, yy = x = 1;
	while(b) {
		ll q = a / b, t = b;
		b = a % b, a = t, t = xx, xx = x - q * xx;
		x = t, t = yy, yy = y - q * yy, y = t;
	}
	d = a;
}

struct P {
	ll r, m;
	ll minpos;
};

// Solves x = a1 mod m1, x = a2 mod m2, x is unique modulo lcm(m1, m2).
// Returns {0, -1} on failure, {x, lcm(m1, m2)} otherwise.
P crt(ll a1, ll m1, ll a2, ll m2) {
	ll s, t, d;
	extended_euclid(m1, m2, s, t, d);
	if(a1 % d != a2 % d) return P{0ll, -1ll, 0ll};
	return P{mod(s * a2 % m2 * m1 + t * a1 % m1 * m2, m1 * m2) / d, m1 / d * m2, 0ll};
}
P crt(P l, P r) {
	auto x   = crt(l.r, l.m, r.r, r.m);
	x.minpos = max(l.minpos, r.minpos);
	return x;
}

ll solve(vector<vector<P>>::iterator begin, vector<vector<P>>::iterator end, P prefix = {0, 1, 0}) {
	if(begin == end) {
		// make sure we go beyond minpos
		if(prefix.r < prefix.minpos) {
			// prone to errors, so make WA variants
			prefix.r += prefix.m * (1 + (prefix.minpos - prefix.r - 1) / prefix.m);
		}
		return prefix.r;
	}

	ll best = 0;
	for(auto &x : *begin) {
		P p    = crt(prefix, x);
		auto r = solve(begin + 1, end, p);
		if(best == 0 || r < best) { best = r; }
	}
	return best;
}

int main() {
	ll n;
	cin >> n;
	map<ll, map<ll, ii>> c;
	while(n--) { // read input
		ll p, d;
		cin >> p >> d;
		auto &x = c[d][p % d];
		++x.first;
		x.second = max(x.second, p);
	}
	ii m{0, 1};
	ll count = 0, minp = 0;
	vector<vector<P>> ps;
	ll prod = 1;
	for(auto &_ : c) {      // find max per distance
		auto &p = _.first;  // prime
		auto &x = _.second; // residues map: {residue class -> {count, max}}
		auto max_count =
		    max_element(x.begin(), x.end(), [](const pair<ll, ii> &l, const pair<ll, ii> &r) {
			    return l.second.first < r.second.first;
			})->second.first;
		count += max_count;
		prod *= p;
		ps.push_back({});
		for(auto &_ : x) {
			const auto &r = _.first, &count = _.second.first, &max = _.second.second;
			if(count == max_count) { ps.back().push_back({r, p, max}); }
		}
	}

	assert(prod <= 1000000000000ll);

	auto r = solve(ps.begin(), ps.end(), {0, 1, 0});
	cout << r << ' ' << count << endl;
	return 0;
}
