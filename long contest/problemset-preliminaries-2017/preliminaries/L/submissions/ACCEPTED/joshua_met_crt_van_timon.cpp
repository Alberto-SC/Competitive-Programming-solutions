#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <limits>

/*
I copied the crt from Timon, and put it in my solution.
Should work just fine. 
*/

using namespace std;

using ll = long long int;

constexpr ll MAX = (1LL << 62);

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

pair<ll, ll> align(pair<ll, ll> pos, ll incpos) {
    ll jump = pos.second;
    ll jumps = max(0LL, (incpos - pos.first + jump - 1) / jump);
    if (jumps > MAX / jump)
        return {0LL, -1LL};
    else
        return {pos.first + jumps * jump, pos.second};
}


// do a CRT here
pair<ll, ll> merge(pair<ll, ll> lhs, pair<ll, ll> rhs) {
    auto cr = crt(lhs.second % lhs.first, lhs.first, rhs.second % rhs.first, rhs.first);
    assert(cr.second >= 0);

    cr = align(cr, lhs.second);
    cr = align(cr, rhs.second);
    assert(cr.second >= 0);

    return {cr.second, cr.first};
}

int main () {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n;
    cin >> n;

    // for each jump distance, gather all frogs
    unordered_map<ll, vector<ll>> classes;
    for (int i = 0; i < n; ++i) {
        ll x, d;
        cin >> x >> d;

        classes[d].push_back(x);
    }

    // for each jump distance we have a starting position
    vector<pair<ll, vector<ll>>> dists_locs;
    ll size_of_tower = 0;
    for (const auto p : classes) {
        const auto d = p.first;

        // for each starting position, gather the number of frogs and biggest location
        // vector does not work, d is too big
        unordered_map<ll, pair<ll, ll>> mod_classes;

        ll biggest_cls = 0;

        for (const auto x : p.second) {
            const auto clas = x % d;
            auto & p = mod_classes[clas];
            p.first++;
            p.second = max(p.second, x);

            if (p.first > biggest_cls) {
                biggest_cls = p.first;
            }
        }

        vector<ll> biggest_idx;
        for (const auto p : mod_classes) {
            if (p.second.first == biggest_cls) {
                biggest_idx.push_back(p.second.second);
            }
        }

        assert(!biggest_idx.empty());
        size_of_tower += biggest_cls;
        dists_locs.emplace_back(d, biggest_idx);
    }

    vector<pair<ll, ll>> chain;
    chain.reserve(dists_locs.size());

    function<ll(int)> recurse = [&](int i) {
        if (i < dists_locs.size()) {
            ll mini = numeric_limits<ll>::max();
            for (const auto & p : dists_locs[i].second) {
                pair<ll, ll> res = {dists_locs[i].first, p};

                if (i > 0) {
                    const auto acc = chain[i-1];
                    res = merge(acc, res);
                }

                chain.push_back(res);
                mini = min(mini, recurse(i+1));
                assert(mini != ll(-1));
                chain.pop_back();
            }
            return mini;
        } else {
            return chain.back().second;
        }
    };

    const auto ans = recurse(0);
    assert(ans != ll(-1));

    cout << ans << ' ' << size_of_tower << endl;
}