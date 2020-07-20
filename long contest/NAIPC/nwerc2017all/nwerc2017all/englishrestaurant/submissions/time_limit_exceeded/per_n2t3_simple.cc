#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100, MAX_T = 100;

int n, G, T;
vector<int> C;
double mu[MAX_N+1][MAX_N+1][MAX_T+1][MAX_T+1] = {};

double Mu(int i, int j, int t, int u) {
    if (i > j && u == 0) return 1.0;
    if (u > t) return 0.0;
    if (j == 0) return u <= t-1;
    double &res = mu[i][j][t][u];
    if (res == 0) {
        double bin = 1, p = 1.0*(C[j]-C[j-1])/C[j], pp = 1, qp = pow(1-p, t);
        for (int x = 0; x <= t; ++x) {
            res += bin * pp * qp * Mu(i, j-1, t-x, j < n ? max(0, u-x+1) : 0);
            bin = bin * (t-x) / (x+1);
            pp *= p;
            qp /= 1-p;
        }
        ++res;
    }
    return res-1;
}

int main(void) {
    scanf("%d%d%d", &n, &G, &T);
    C.resize(n);
    for (auto &c: C) {
        scanf("%d", &c);
        if (c > G) c = G;
    }
    C.push_back(G);
    sort(C.begin(), C.end());

    double ans = 0;
    for (int t = 0; t < T; ++t) {
        int i = 0;
        for (int x = 1; x <= G; ++x) {
            while (i < n && C[i] < x) ++i;
            ans += (1 - Mu(i, n, t, 0)) * x / G;
        }
    }
    printf("%.9lf\n", ans);
}
