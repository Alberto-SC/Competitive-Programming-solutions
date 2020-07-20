#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

/*
This solution is a bit less naive than Jeroen's (I think)
We do all the preprocessing: determine which groups of frogs matter
and compute the size of the biggest tower.
Then we "simulate" the jumping for the remaining frogs, multiple jumps at a time.
This runs quite fast!
*/

using namespace std;

using ll = long long unsigned int;

// NAIVE, should do a CRT here
pair<ll, ll> merge(pair<ll, ll> lhs, pair<ll, ll> rhs) {
loop: // I was too lazy to write a while or for loop
    if (lhs.second == rhs.second) {
        return {lhs.first * rhs.first, lhs.second};
    }

    if (lhs.second > rhs.second) swap(lhs, rhs);
    
    // this check is not needed, but we avoid a division this way
    if (lhs.second + lhs.first >= rhs.second) {
        lhs.second += lhs.first;
        goto loop;
    }
    const auto diff = rhs.second - lhs.second;
    const auto m = (diff - 1) / lhs.first + 1;
    lhs.second += m * lhs.first;
    goto loop;
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

    sort(dists_locs.begin(), dists_locs.end());
    reverse(dists_locs.begin(), dists_locs.end());

    vector<pair<ll, ll>> chain;
    chain.reserve(dists_locs.size());

    function<ll(int)> recurse = [&](int i) {
        if (i < dists_locs.size()) {
            ll mini = ll(-1); // unsigned
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