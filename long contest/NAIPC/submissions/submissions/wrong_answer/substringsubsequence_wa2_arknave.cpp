#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAXN = 100005;
constexpr int MAXM = 102;
int n, m;
char s[MAXN], t[MAXM];

/**
 * Counts where t is a subarray
 */
int main() {
    scanf(" %s %s", s, t);
    n = strlen(s);
    m = strlen(t);
    int ans = 0;
    for (int i = 0; i + m <= n; ++i) {
        bool match = true;
        for (int j = 0; match and j < m; ++j) {
            match &= s[i + j] == t[j];
        }

        ans += match;
    }
    printf("%d\n", ans);
    return 0;
}
