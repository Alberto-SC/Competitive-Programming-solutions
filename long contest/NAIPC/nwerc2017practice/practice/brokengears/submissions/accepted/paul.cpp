#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FOR(i,a,b) for (ll i = (a); i < (b); i++)

const ll N = 100100;
ll a[N], b[N];
vector<pair<ll,ll>> adj[N];

int main() {
	ll n; cin >> n;
	
	vector<ll> r(n);
	FOR(i,0,n) cin >> r[i];

	ll rmax = 0, rsum = 0;
	FOR(i,0,n) rmax = max(rmax,r[i]), rsum += r[i];

	ll m; cin >> m;
	while (m--) {
		ll u, v, w; cin >> u >> v >> w;
		u--, v--;
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}

	queue<ll> q;
	a[0] = 1;
	q.push(0);

	while (q.size()) {
		ll u = q.front(); q.pop();
		for (const auto &e: adj[u]) {
			ll v, w;
			tie(v,w) = e;
			if (a[v]) continue;
			a[v] = -a[u], b[v] = w-b[u];
			q.push(v);
		}
	}
	
	vector<ll> xs;
	ll asum = 0, bsum = 0;
	FOR(i,0,n) asum += a[i];
	FOR(i,0,n) bsum += b[i];
	
	if (asum) xs.push_back((rsum-bsum)/asum);
	
	ll i_pos = -1, i_neg = -1;
	FOR(i,0,n) if (a[i] == +1 && (i_pos == -1 || b[i] > b[i_pos])) i_pos = i;
	FOR(i,0,n) if (a[i] == -1 && (i_neg == -1 || b[i] > b[i_neg])) i_neg = i;
	
	for (ll i: {i_pos,i_neg}) if (i != -1) xs.push_back((rmax-b[i])/a[i]);

	for (const ll x: xs) {
		bool ok = true;
		FOR(u,0,n) for (const auto &e: adj[u]) {
			ll v, w;
			tie(v,w) = e;
			if ((a[u]+a[v])*x + b[u]+b[v] != w) ok = false;
		}
		if (!ok) continue;
		
		map<ll,vector<ll>> gears;
		vector<ll> res(n);
		FOR(i,0,n) gears[r[i]].push_back(i+1);
		FOR(u,0,n) {
			auto &g = gears[ a[u]*x + b[u] ];
			if (g.empty()) ok = false;
			else res[u] = g.back(), g.pop_back();
		}	
		if (!ok) continue;

		FOR(i,0,n) cout << res[i] << " \n"[i+1 == n];
		return 0;
	}
	cout << "impossible" << endl;
}
