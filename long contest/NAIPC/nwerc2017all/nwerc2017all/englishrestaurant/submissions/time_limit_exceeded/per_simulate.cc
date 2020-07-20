#include <bits/stdc++.h>
using namespace std;

const int TRUNC = 500000;

typedef long long ll; // need to switch to int128 if n grows to 100

struct state {
    ll taken;
    double prob;
    double E;
    state(ll taken=0, double prob=1, double E=0): taken(taken), prob(prob), E(E) {}
    bool operator<(const state &s) { return prob > s.prob; }
};

int main(void) {
    int N, G, T;
    scanf("%d%d%d", &N, &G, &T);
    vector<int> S(N);
    for (int &x: S) {
        scanf("%d", &x);
        if (x > G) x = G;
    }
    sort(S.begin(), S.end(), greater<int>());
    S.push_back(0);
    vector<double> P(N), E(N);
    double loss_p = 1.0;
    for (int i = 0; i < N; ++i) {
        P[i] = 1.0 * (S[i] - S[i+1]) / G;
        loss_p -= P[i];
        if (S[i] > S[i+1]) {
            for (int s = S[i+1]+1; s <= S[i]; ++s)
                E[i] += s;
            E[i] /= G;
        }
    }

    vector<state> cur, nxt;
    cur.push_back(state());
    for (int t = 0; t < T; ++t) {
        //        printf("go T = %d\n", t);
        nxt.clear();
        for (const auto &st: cur) {
            if (st.taken == (1LL<<N)-1) {
                nxt.emplace_back(st);
                continue;
            }
            double tot_loss = loss_p;
            int tbl = 0;
            double tot_p = 0.0, tot_E = 0.0;
            for (int i = 0; i < N; ++i) {
                //                printf("  i %d\n", i);
                if (!(st.taken & (1LL<<i))) {
                    if (tbl && tot_p > 0) {
                        nxt.emplace_back(state(st.taken | tbl, st.prob * tot_p, st.E + tot_E/tot_p));
                    } else if (i) {
                        tot_loss += tot_p;
                    }
                    tot_p = tot_E = 0;
                    tbl = 1LL<<i;
                }
                tot_p += P[i];
                tot_E += E[i];
            }
            nxt.emplace_back(state(st.taken | tbl, st.prob * tot_p, st.E + tot_E/tot_p));
            if (tot_loss > 0)
                nxt.emplace_back(state(st.taken, st.prob * tot_loss, st.E));
        }
        cur.clear();

        // aggregate
        sort(nxt.begin(), nxt.end(),
             [](const state &A, const state &B) { return A.taken < B.taken; });
        for (int i = 0; i < nxt.size(); ) {
            int f = i;
            double tot_p = 0.0, tot_e = 0.0;
            while (i < nxt.size() && nxt[i].taken == nxt[f].taken) {
                tot_p += nxt[i].prob;
                tot_e += nxt[i].prob * nxt[i].E;
                ++i;
            }
            if (tot_p > 1e-11)
                cur.emplace_back(state(nxt[f].taken, tot_p, tot_e/tot_p));
        }
        
        sort(cur.begin(), cur.end());

        if (cur.size() > TRUNC)
            cur.resize(TRUNC);
        
    }

    double ans = 0;
    for (auto &st: cur)
        ans += st.prob * st.E;

    printf("%.9lf\n", ans);
    
}
/*

4 57 5
10 29 45 57

 */
