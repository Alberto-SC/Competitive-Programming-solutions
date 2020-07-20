#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000;
const int MAX_LOG_N = 17;
int N, Q;

// dsu
int dsu[MAX_N];
int root(int u) {
    if (dsu[u] < 0) return u;
    return (dsu[u] = root(dsu[u]));
}
void unite(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    if (-dsu[u] > -dsu[v]) swap(u, v);
    dsu[v] += dsu[u];
    dsu[u] = v;
}
bool same(int u, int v) {
    return root(u) == root(v);
}

int dep[MAX_N];
int btn[MAX_LOG_N][MAX_N];
int par[MAX_LOG_N][MAX_N];

struct Edge { int to, w; };
vector<Edge> g[MAX_N];

void dfs(int u, int p, int d) {
    dep[u] = d;
    par[0][u] = p;
    for (Edge e : g[u]) {
        if (e.to != p) {
            btn[0][e.to] = e.w;
            dfs(e.to, u, d + 1);
        }
    }
}

void build() {
    for (int u = 0; u < N; u++) {
        if (dep[u] == -1) {
            dfs(u, -1, 0);
        }
    }

    for (int i = 0; i + 1 < MAX_LOG_N; i++) {
        for (int u = 0; u < N; u++) {
            if (par[i][u] == -1) {
                par[i + 1][u] = -1;
                btn[i + 1][u] = 0;
            }
            else {
                par[i + 1][u] = par[i][par[i][u]];
                btn[i + 1][u] = max(btn[i][u], btn[i][par[i][u]]);
            }
        }
    }
}

int lca(int u, int v) {
    int mx = -1;
    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int i = MAX_LOG_N - 1; i >= 0; i--) {
        if (diff & (1 << i)) {
            mx = max(mx, btn[i][v]);
            v = par[i][v];
        }
    }
    if (u == v) return mx;
    for (int i = MAX_LOG_N - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) {
            mx = max(mx, btn[i][u]);
            mx = max(mx, btn[i][v]);
            u = par[i][u];
            v = par[i][v];
        }
    }
    mx = max(mx, max(btn[0][u], btn[0][v]));
    return mx;
}

struct Oper {
    int id, cmd, u, v;
};
vector<Oper> operations;

int main() {
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d %d", &N, &Q);

        // init
        fill(dep, dep + N, -1);
        for (int i = 0; i < MAX_LOG_N; i++) {
            fill(btn[i], btn[i] + N, -1);
            fill(par[i], par[i] + N, -1);
        }
        for (int i = 0; i < N; i++)
            g[i].clear();
        operations.clear();

        for (int id = 1; id <= Q; id++) {
            int cmd, u, v;
            scanf("%d %d %d", &cmd, &u, &v);
            u--; v--;
            operations.push_back((Oper) {id, cmd, u, v});
        }

        // construct mst(s)
        fill(dsu, dsu + N, -1);
        for (Oper op : operations) {
            int u = op.u, v = op.v;
            if (op.cmd == 1) {
                if (!same(u, v)) {
                    unite(u, v);
                    g[u].push_back((Edge) {v, op.id});
                    g[v].push_back((Edge) {u, op.id});
                }
            }
        }

        build(); // build lca, btn on mst(s)
        fill(dsu, dsu + N, -1);
        for (Oper op : operations) {
            int u = op.u, v = op.v;
            if (op.cmd == 1) {
                if (!same(u, v)) {
                    unite(u, v);
                }
            }
            else {
                if (!same(u, v)) puts("-1");
                else {
                    printf("%d\n", lca(u, v));
                }
            }
        }
    }

    return 0;
}