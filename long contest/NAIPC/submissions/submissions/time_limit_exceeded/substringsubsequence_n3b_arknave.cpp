#include <cstdio>
#include <cstring>

using namespace std;

constexpr int MAXN = 100005;
constexpr int MAXM = 102;
int n, m;
char s[MAXN], t[MAXM];

bool subseq(int start, int end) {
    int p = 0;
    for (int i = start; p < m and i < end; ++i) {
        if (s[i] == t[p])
            ++p;
    }

    return p == m;
}

int main() {
    scanf(" %s %s", s, t);
    n = strlen(s);
    m = strlen(t);

    long long ans = 0LL;
    int j = 1;
    for (int i = 0; i < n; ++i) {
        while (j < n and !subseq(i, j)) {
            ++j;
        }
        if (j == n and !subseq(i, j)) {
            break;
        }
        ans += n + 1 - j;
    }

    printf("%lld\n", ans);

    return 0;
}
