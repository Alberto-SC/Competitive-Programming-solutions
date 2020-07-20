#include <bits/stdc++.h>
using namespace std;

vector<int> a, parent, prv, nxt;

void prepare(int n, int LIM) {
    int div[LIM+1];
    memset(div, 0, sizeof(div));
    for (int i = 2; i <= LIM; ++i)
        if (!div[i])
            for (int j = i; j <= LIM; j += i)
                div[j] = i;
    vector<int> last(LIM+1, -1);
    prv = vector<int>(n, -1);
    nxt = vector<int>(n, n);
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        while (v != 1) {
            int &l = last[div[v]];
            if (l < i) {
                prv[i] = max(prv[i], l);
                if (l != -1)
                    nxt[l] = min(nxt[l], i);
            }
            l = i;
            v /= div[v];
        }
    }
}

bool solve(int L, int R, int par) {
    if (R-L <= 0) return true;
    for (int i = L, j = R-1; i <= j; ++i, --j) {
        parent[i] = par;
        if (prv[i] < L && nxt[i] >= R)
            return solve(L, i, i) && solve(i+1, R, i);
        parent[j] = par;
        if (prv[j] < L && nxt[j] >= R)
            return solve(L, j, j) && solve(j+1, R, j);
    }
    return false;
}

int main(void) {
    int n, max_a = 0;
    scanf("%d", &n);
    a.resize(n);
    for (auto &x: a) {
        scanf("%d", &x);
        max_a = max(x, max_a);
    }
    prepare(n, max_a);
    parent.resize(n);
    if (solve(0, n, -1))
        for (int i = 0; i < n; ++i)
            printf("%d ", parent[i]+1);
    else
        printf("impossible\n");    
}
