#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
int main() {
    int n, c; cin >> n >> c;
    vector<tuple<int, int, int>> a;
    rep(i,0,n) {
        int d, I;
        cin >> d >> I;
        a.push_back(make_tuple(I - d, d, i));
    }

    sort(a.begin(), a.end());

    vector<int> best(c + 1, 0);
    vector<int> prev(c + 1, -1);
    vector<int> prev_idx(c + 1, -1);
    prev[0] = 0;
    for (const auto& x : a) {
        int dif, d, I, idx;
        tie(dif, d, idx) = x;
        I = dif + d;
        int bdr = c - max(d, I);
        for (int i = bdr; i >= 0; i--) if (prev[i] >= 0) {
            if (best[i] + 1 > best[i + I]) {
                best[i + I] = best[i] + 1;
                prev[i + I] = i;
                prev_idx[i + I] = idx;
            }
        }
    }

    int pos = 0;
    rep(i,0,best.size()) if (best[i] > best[pos]) pos = i;
    cout << best[pos] << endl;

    vector<int> res;
    while (pos > 0) {
        res.push_back(prev_idx[pos]);
        pos = prev[pos];
    }
    reverse(res.begin(), res.end());
    for (int x : res) cout << x + 1 << " ";
    cout << endl;
}
