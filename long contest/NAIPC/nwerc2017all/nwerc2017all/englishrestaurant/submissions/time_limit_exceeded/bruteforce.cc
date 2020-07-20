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
typedef pair<int, int> pii;
typedef vector<int> vi;
int n, g, t;
vi c;
double go(int steps, vector<bool>& taken) {
    if (steps == 0) return 0;
    double expected = 0;
    int prev_size = 0;
    rep(i,0,n) {
        if (!taken[i]) {
            // table i is occupied with probability frac by a group of size group_size on avg.
            double group_size = (c[i] + prev_size + 1) / 2.0;
            double frac = (c[i] - prev_size) / double(g);
            taken[i] = true;
            expected += frac * (go(steps - 1, taken) + group_size);
            taken[i] = false;
            prev_size = c[i];
        }
    }
    double frac = 1 - prev_size / double(g); // overflow case
    return expected + frac * go(steps - 1, taken);
}
int main() {
    cin >> n >> g >> t;
    c.resize(n);
    rep(i,0,n) {
        cin >> c[i];
        c[i] = min(g, c[i]);
    }
    sort(c.begin(), c.end());

    vector<bool> taken(n);
    double res = go(t, taken);
    printf("%.9lf\n", res);
}
