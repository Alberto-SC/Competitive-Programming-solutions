#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> A;

int main(void) {
    int n, c;
    scanf("%d%d", &n, &c);
    int d[n], s[n], idx[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", d+i, s+i);
        idx[i] = i;
    }
    sort(idx, idx+n, [&](int x, int y) { return s[x] - d[x] < s[y] - d[y]; });
    int rem[n+1][n+1];
    memset(rem, -1, sizeof(rem));
    rem[0][0] = c;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            if (j && rem[i][j-1] >= d[idx[i]])
                rem[i+1][j] = max(rem[i][j], rem[i][j-1] - s[idx[i]]);
            else
                rem[i+1][j] = rem[i][j];
    int m = n;
    while (rem[n][m] < 0) --m;
    printf("%d\n", m);
    vector<int> ans;
    while (n > 0) {
        --n;
        if (rem[n][m] != rem[n+1][m]) {
            ans.push_back(idx[n]+1);
            --m;
        }
    }
    for (; !ans.empty(); ans.pop_back())
        printf("%d\n", ans.back());
    return 0;
}
