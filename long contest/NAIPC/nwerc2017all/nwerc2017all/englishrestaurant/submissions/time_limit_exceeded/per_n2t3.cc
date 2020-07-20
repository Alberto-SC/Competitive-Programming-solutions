#include <bits/stdc++.h>
using namespace std;

vector<int> C;
double mu[101][101][101][101];

double Mu(int i, int j, int u, int t) {
    if (u > t) return 0.0;
    if (t == 0) return i > j && u == 0;
    if (j == 0) return u == t-1;
    double &res = mu[i][j][u][t];
    if (res == 0) {
        double p = 1.0*(C[j]-C[j-1])/C[j], pp = 1.0, qp = pow(1-p, t), bin = 1;
        if (u == 0 && j < i)
            res = Mu(i, j-1, 0, t) * qp;
        for (int x = 0; x <= u+1 && x <= t; ++x) {
            double P = bin*pp*qp;
            double Q = Mu(i, j-1, u-x+1, t-x);
            res += P*Q;
            bin = bin * (t-x) / (x+1);
            pp *= p;
            qp /= 1-p;
        }
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
    sort(C.begin(), C.end());
    memset(mu, 0, sizeof(mu));
    
    double cprob[101][101] = {}, fprob[101][101] = {};
    for (int t = 0; t <= T; ++t)
        for (int i = 0; i <= n; ++i) {
            for (int u = 0; u <= t; ++u)
                cprob[t][i] += Mu(i, n-1, u, t);
        }

    if (C[n-1] < G) {
        for (int t = 0; t <= T; ++t)
            for (int i = 0; i <= n; ++i) {
                double bin = 1.0, p = 1.0*C[n-1]/G;
                for (int nt = 0; nt <= t; ++nt) {
                    double P = bin * pow(p, t-nt) * pow(1-p, nt);
                    fprob[t][i] += P * cprob[t-nt][i];
                    bin = bin * (t-nt) / (nt+1);
                }
            }
        memcpy(cprob, fprob, sizeof(fprob));
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
