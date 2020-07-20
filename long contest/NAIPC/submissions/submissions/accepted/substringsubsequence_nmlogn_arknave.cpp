#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAXN = 100005;
constexpr int MAXM = 102;
constexpr int SIGMA = 26;
int n, m;
char s[MAXN], t[MAXM];
vector<int> by_char[SIGMA];

/**
 * O(nm log(n)) solution
 * Iterate over all starting points. Do a binary search to find the next index.
 */
int main() {
    scanf(" %s %s", s, t);
    n = strlen(s);
    m = strlen(t);
    for (int i = 0; i < n; ++i) {
        by_char[s[i] - 'a'].push_back(i);
    }
    long long ans = 0LL;
    for (int i = 0; i < n; ++i) {
        int p = i;
        for (int j = 0; j < m; ++j) {
            int c = t[j] - 'a';
            int idx = lower_bound(begin(by_char[c]), end(by_char[c]), p) - begin(by_char[c]);
            if (idx == by_char[c].size()) {
                p = n + 1;
                break;
            } else {
                p = by_char[c][idx] + 1;
            }
        }

        if (p <= n) {
            ans += n + 1 - p;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
