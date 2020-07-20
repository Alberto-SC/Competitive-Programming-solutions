#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100, MAX_T = 100;

vector<int> C;
double nu[MAX_N][MAX_T][MAX_T] = {}, mu[MAX_N][MAX_T][MAX_T] = {};
double phit[MAX_N+1][MAX_T][MAX_T];

double Nu(int j, int t, int u) {
    if (u == 0 || u <= t-j-1) return 1.0;
    if (u >= t || t == 0) return 0.0;
    if (j == 0) return u <= t-1;
    double &res = nu[j][t][u];
    if (res == 0) {
        for (int x = 0; x <= t; ++x)
            res += phit[j][t][x] * Nu(j-1, t-x, max(0, u-x+1));
        ++res;
    }
    return res-1;
}

double Mu(int i, int j, int t, int u) {
    if (j < i) return Nu(j, t, u);
    if (u + j - i + 1 > t) return 0.0;
    if (j == 0) return u <= t-1;
    double &res = mu[j][t][u];
    if (res == 0) {
        for (int x = 0; x <= t; ++x)
            res += phit[j][t][x] * Mu(i, j-1, t-x, max(0, u-x+1));
        ++res;
    }
    return res-1;
}

int main(void) {
    int n, G, T;
    scanf("%d%d%d", &n, &G, &T);
    C.resize(n);
    for (auto &c: C) {
        scanf("%d", &c);
        if (c > G) c = G;
    }
    C.push_back(G);
    sort(C.begin(), C.end());

    for (int j = 1; j <= n; ++j)
        for (int t = 0; t < T; ++t) {
            double bin = 1, p = 1.0*(C[j]-C[j-1])/C[j];
            for (int x = 0; x <= t; ++x) {
                phit[j][t][x] = bin * pow(p, x) * pow(1-p, t-x);
                bin = bin * (t-x) / (x+1);
            }
        }
    
    double cprob[MAX_T][MAX_N+1] = {};
    for (int i = 0; i <= n; ++i) {
        memset(mu, 0, sizeof(mu));
        for (int t = 0; t < T; ++t)
            for (int x = 0; x <= t; ++x)
                cprob[t][i] += phit[n][t][x] * Mu(i, n-1, t-x, 0);
    }
    
    double ans = (1.0+G)/2 * T;
    for (int t = 0; t < T; ++t) {
        int i = 0;
        for (int x = 1; x <= G; ++x) {
            while (i < n && C[i] < x) ++i;
            ans -= cprob[t][i] * x / G;
        }
    }
    printf("%.9lf\n", ans);
}
