#include <cstdio>
#include <cstring>

using namespace std;

constexpr int MAXN = 100005;
constexpr int MAXM = 102;
int n, m;
char s[MAXN], t[MAXM];

int main() {
    scanf(" %s %s", s, t);
    n = strlen(s);
    m = strlen(t);

    long long ans = 0LL;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int p = 0;
            for (int k = i; k < j; ++k) {
                if (p < m and s[k] == t[p])
                    ++p;
            }

            if (p == m) ++ans;
        }
    }

    printf("%lld\n", ans);

    return 0;
}
