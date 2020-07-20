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
// jmp[i][j] = smallest k such that k >= i and s[k] == j
int jmp[MAXN][SIGMA];

/**
 * O(n * sigma + nm) solution
 */
int main() {
    scanf(" %s %s", s, t);
    n = strlen(s);
    m = strlen(t);
    for (int j = 0; j < SIGMA; ++j) {
        jmp[n][j] = n + 1;
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < SIGMA; ++j) {
            jmp[i][j] = jmp[i + 1][j];
        }
        jmp[i][s[i] - 'a'] = i;
    }

    long long ans = 0LL;
    for (int i = 0; i < n; ++i) {
        int p = i;
        for (int j = 0; j < m; ++j) {
            int c = t[j] - 'a';
            p = jmp[p][c] + 1;
            if ((p == n and j + 1 < m) or (p > n)) {
                p = n + 1;
                break;
            }
        }

        if (p <= n) {
            ans += n + 1 - p;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
