
#include <bits/stdc++.h>
using namespace std;
//HLD edgdes indexado desde 1 NoLazy  
//chainNo - current Chain while making HLD
//chainInd[x] - Given x node, to which chain does x belong to.
//posInBase[x] - Given x node - what is the position of x in baseArray.
//chainHead[y] - Given y chain, what is the head of the chain
//subsize[y] - Given a chain, what is the length of the chain
const int MAXN = 100009;
const int LN = 17;
typedef pair<int, int> pii;
vector< pii > grafo[MAXN]; //first v, second cost of the edge
vector<int> indexx[MAXN]; //thing to know index of the edge
int otherEnd[MAXN]; //same for the index m9
int baseArray[MAXN], ptr; //BaseArray and the size of ST to buil it
int chainNo, chainInd[MAXN], chainHead[MAXN], posInBase[MAXN], subsize[MAXN]; //explained above
int level[MAXN], P[LN][MAXN], loga[LN]; //LCA stuff m8
int ST[MAXN * 3]; //SegTree structure

/* Actual HL-Decomposition part
 * Initially all entries of chainHead[] are set to -1.
 * So when ever a new chain is started, chain head is correctly assigned.
 * As we add a new node to chain, we will note its position in the baseArray.
 * In the first for loop we find the child node which has maximum sub-tree size.
 * The following if condition is failed for leaf nodes.
 * When the if condition passes, we expand the chain to special child.
 * In the second for loop we recursively call the function on all normal nodes.
 * chainNo++ ensures that we are creating a new chain for each normal child.
 */
 
 void HLD(int curNode, int cost, int prev) {
   if (chainHead[chainNo] == -1) 
    chainHead[chainNo] = curNode;
  ptr++;
  chainInd[curNode] = chainNo;
  posInBase[curNode] = ptr; // Position of this node in baseArray which we will use in Segtree
  baseArray[ptr] = cost;
  
  int sc = -1, ncost, lim = grafo[curNode].size();  
  
  for (int i = 0; i < lim; ++i){
    int v = grafo[curNode][i].first;
    if (v == prev) continue;
    if (sc == -1 || subsize[sc] < subsize[v]) {
      sc = v;
      ncost = grafo[curNode][i].second;
    }
  }
  
  if (sc != -1)
    HLD(sc, ncost, curNode);
  
  for (int i = 0; i < lim; ++i) {
    int v = grafo[curNode][i].first;
    if (v == prev || v == sc) continue;
    chainNo++;
    HLD(v, grafo[curNode][i].second, curNode);
  }
  return;
}

int LCA(int x, int y) {
  if (level[x] < level[y]) swap(x, y);
  
  for (int i = LN - 1; i >= 0; --i)
    if (level[x] - (1 << i) >= level[y])
      x = P[i][x];
  
  if (x == y) return x;
  
  for (int i = LN - 1; i >= 0; --i)
    if (P[i][x] != P[i][y]) {
      x = P[i][x];
      y = P[i][y];
    }
  
  return P[0][x];
}

void PreLCA(int n) {
  for (int j = 1; j < LN; ++j) 
    for (int i = 1; i <= n; ++i)
      P[j][i] = P[j - 1][P[j - 1][i]];
  return;
}

void DFS(int cur, int prev, int len) {
  level[cur] = len;
  P[0][cur] = prev;
  subsize[cur] = 1;
  int lim = grafo[cur].size();
  for (int i = 0; i < lim; ++i) { 
    int v = grafo[cur][i].first; 
    if (v == prev) continue;
    otherEnd[indexx[cur][i]] = v;
    DFS(v, cur, len + 1);
    subsize[cur] += subsize[v];
  }
  return;
}

void Init(int n) {
  for (int i = 0; i <= n; ++i) {
    chainHead[i] = -1;
    for (int j = 0; j < LN; ++j) P[j][i] = -1;
  }
  return;
}

//ST STUFF
void build_ST(int n, int l, int r) {
  if (l == r) {
    ST[n] = baseArray[l];
    return;
  }
  int lc (n << 1), rc = lc | 1, m = (l + r) >> 1;
  build_ST(lc, l, m);
  build_ST(rc, m + 1, r);
  ST[n] = ST[lc] + ST[rc];
  return;
}

void updateSegTree(int n, int L, int R, int i, int val) {
  if (L == R) {
    ST[n] = val;
    return;
  }
  int lc = n << 1, rc = lc | 1, m = (L + R) >> 1;
  if (i <= m) updateSegTree(lc, L, m, i, val);
  else updateSegTree(rc, m + 1, R, i, val);
  ST[n] = ST[lc] + ST[rc];
}

int querySegTree(int n, int L, int R, int l, int r) {
  if (R < l|| L > r) return 0;
  if (L >= l && R <= r) return ST[n];
  int lc = n << 1, rc = lc | 1, m = (L + R) >> 1;
  int lv = querySegTree(lc, L, m, l, r);
  int rv = querySegTree(rc, m + 1, R, l, r);
  return lv + rv;
}

int queryUp(int u, int v) {
  if (u == v) return 0;
  int lchain, rchain = chainInd[v], ans = 0;
  while (1) {
    lchain = chainInd[u];
    if (lchain == rchain) {
      if (u == v) break;
      int currAns = querySegTree(1, 1, ptr, posInBase[v] + 1, posInBase[u]);
      ans += currAns;
      break;
    }
    int currAns = querySegTree(1, 1, ptr, posInBase[chainHead[lchain]], posInBase[u]);
    ans += currAns;
    u = chainHead[lchain];
    u = P[0][u];
  }
  return ans;
}

int queryPath(int u, int v) {
  int lca = LCA(u, v);
  int a = queryUp(u, lca);
  int b = queryUp(v, lca);
  return a + b;
}

void Update(int i, int val) {
  int node = otherEnd[i];
  updateSegTree(1, 1, ptr, posInBase[node], val);
}

int main() {
  cin.tie(0); ios_base::sync_with_stdio(0);
  ptr = 0;
  int n;
  cin >> n;
  Init(n);
  for (int i = 1; i < n; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    grafo[u].push_back(pii(v, c));
    grafo[v].push_back(pii(u, c));
    indexx[u].push_back(i);
    indexx[v].push_back(i);
  }
  DFS(1, 0, 0); //set subsize, depth, and parent for each node, 0 here is the root
  PreLCA(n);
  ptr = -1;
  chainNo = 1;
  HLD(1, 0, 0); //decompose tree and make baseArray
  build_ST(1, 1, ptr); //construct ST;
  int q, op, u, v;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    cin >> op >> u >> v;
    if (op == 1) {
      Update(u, v);
      continue;
    }
    cout << queryPath(u, v) << '\n';
  }
  return 0;
}

//// HLD de nodos indexado desde 0, NoLazy
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50100;
const int MAXK = 17;
int N, nv[MAXN], q; //N, node value, queries
int st[MAXN << 2], barray[MAXN]; //segtree, base array

int query(int i, int j, int n = 0, int l = 0, int r = N - 1) {
  if (j < l || r < i) return 0;
  if (i <= l && r <= j) return st[n];
  return __gcd(query(i, j, (n << 1) + 1, l, (l + r) >> 1),
               query(i, j, (n << 1) + 2, ((l + r) >> 1) + 1, r));
}

void update(int i, int x, int n = 0, int l = 0, int r = N - 1) {
  if (i < l || i > r) return;
  if (l == r){
    st[n] = x;
    return;
  }
  update(i, x, (n << 1) + 1, l, (l + r) >> 1);
  update(i, x, (n << 1) + 2, ((l + r) >> 1) + 1, r);
  st[n] = __gcd(st[(n << 1) + 1], st[(n << 1) + 2]);
}

void build(int n = 0, int l = 0, int r = N - 1) {
  if (l == r) {
    st[n] = barray[l];
    return;
  }
  build((n << 1) + 1, l, (l + r) >> 1);
  build((n << 1) + 2, ((l + r) >> 1) + 1, r);
  st[n] = __gcd(st[(n << 1) + 1], st[(n << 1) + 2]);
}

int g[MAXN], p[MAXN][MAXK], d[MAXN], ix[MAXN], sz[MAXN], nIx; 
//head of the list of the node, parent, level, index in base array, subsize, current index (basearray)
vector < int > grafo[MAXN];

int LCA(int u, int v) {
  if (d[u] < d[v])
    swap(u, v);

  for (int i = MAXK - 1; i >= 0; --i)
    if (d[p[u][i]] >= d[v])
      u = p[u][i];

  if (u == v) return u;

  for (int i = MAXK - 1; i >= 0; --i)
    if (p[u][i] != p[v][i]){
      u = p[u][i];
      v = p[v][i];
    }

  return p[u][0];
}

int size(int n, int pr) {
  sz[n] = 1;
  int lim = grafo[n].size();
  for (int i = 0; i < lim; ++i) {
    int v = grafo[n][i];
    if (v == pr) continue;
    sz[n] += size(v, n);
  }
  return sz[n];
}

void hl(int n, int pr, int grp){
  int best = -1;

  d[n] = (n ? d[pr] : 0) + 1;
  p[n][0] = pr;
  g[n] = grp;

  ix[n] = nIx;
  barray[nIx] = nv[n];
  nIx++;
  int lim = grafo[n].size();
  for (int i = 0; i < lim; ++i) {
    int v = grafo[n][i];
    if (v == pr) continue;
    if (best == -1 || sz[best] < sz[v])
      best = v;
  }

  if (best != -1)
    hl(best, n, grp);

  for (int i = 0; i < lim; ++i) {
    int v = grafo[n][i];
    if (v == pr || v == best) continue;
    hl(v, n, v);
  }
}

int lineQ(int u, int v){
  int ans = 0;

  for (; g[u] != g[v]; u = p[g[u]][0])
    ans = __gcd(ans, query(ix[g[u]], ix[u]));

  ans = __gcd(ans, query(ix[v], ix[u]));

  return ans;
}

int treeQ(int u, int v) {
  int l = LCA(u, v);
  return __gcd(lineQ(u, l), lineQ(v, l));
}

int main() {
  cin.tie(0); ios_base::sync_with_stdio(0);
  while (cin >> N) {
    for (int i = 0; i < N; ++i) {
      cin >> nv[i];
      grafo[i].clear();
    }
      nIx = 0;
    int lim = N - 1;
    for (int i = 0; i < lim; ++i) {
      int u, v;
      cin >> u >> v;
      grafo[u].push_back(v);
      grafo[v].push_back(u);
    }

    size(0, 0);
    hl(0, 0, 0);
    build();

    for (int k = 1; k < MAXK; ++k)
      for (int i = 0; i < N; ++i)
        p[i][k] = p[p[i][k - 1]][k - 1];


    while (q--) {
      int t, u, v;
      cin >> t >> u >> v;
      if (t == 1)
        cout << treeQ(u, v) << '\n';
      else
        update(ix[u], v);
    }
  
  }
  return 0;
}



//HLD nodes, indexado desde 0, Lazy
#include <bits/stdc++.h>
using namespace std;
//HLD de nodos indexado desde 0, Lazy
const int MAXN = 100009;
const int MAXK = 17;

int N, q;
int wst[MAXN * 3], Lazy[MAXN * 3];
int g[MAXN], p[MAXN][MAXK], d[MAXN], ix[MAXN], sz[MAXN], nIx; 
vector < int > grafo[MAXN];

int LCA(int u, int v) {
  if (d[u] < d[v])
    swap(u, v);

  for (int i = MAXK - 1; i >= 0; --i)
    if (d[p[u][i]] >= d[v])
      u = p[u][i];

  if (u == v) return u;

  for (int i = MAXK - 1; i >= 0; --i)
    if (p[u][i] != p[v][i]){
      u = p[u][i];
      v = p[v][i];
    }

  return p[u][0];
}

int query(int i, int j, int n = 0, int l = 0, int r = N - 1) {
  if (j < l || r < i) return 0;
  
  int lc = (n << 1) + 1, rc = lc + 1, size = r - l + 1, m = (l + r) >> 1;
  if ((Lazy[n]) && (l != r)) {
    int sizel = (m - l + 1), sizer = (r - m);
    wst[lc] = sizel - wst[lc];
    Lazy[lc]++;
    Lazy[lc] %= 2;
    wst[rc] = sizer - wst[rc];  
    Lazy[rc]++;
    Lazy[rc] %= 2;
    Lazy[n] = 0;
  }
  if (i <= l && r <= j) return wst[n];
  
  return query(i, j, lc, l, m) +
               query(i, j, rc, m + 1, r);
}

void build(int n = 0, int l = 0, int r = N - 1) {
  if (l == r) {
    wst[n] = 1;
    return;
  }
  int lc = (n << 1) + 1, m = (l + r) >> 1;
  build(lc, l, m);
  build(lc + 1, m + 1, r);
  wst[n] = wst[lc] + wst[lc + 1];
}

void update(int i, int j, int n = 0, int l = 0, int r = N - 1) {
  if (j < l || i > r) return;
  int lc = (n << 1) + 1, rc = lc + 1, size = r - l + 1, m = (l + r) >> 1;
  if ((Lazy[n]) && (l != r)) {
    int sizel = (m - l + 1), sizer = (r - m);
    wst[lc] = sizel - wst[lc];
    wst[rc] = sizer - wst[rc];  
    Lazy[lc]++;
    Lazy[lc] %= 2;
    Lazy[rc]++;
    Lazy[rc] %= 2;
    Lazy[n] = 0;
  }
  
  if (i <= l && r <= j) {
    Lazy[n]++;
    Lazy[n] %= 2;
    wst[n] = size - wst[n];
    return;
  }
  update(i, j, lc, l, m);
  update(i, j, rc, m + 1, r);
  wst[n] = wst[lc] + wst[rc];
}

void lineU(int u, int v){
  for (; g[u] != g[v]; u = p[g[u]][0])
    update(ix[g[u]], ix[u]);
  update(ix[v], ix[u]);
  return;
}

void updatetree(int u, int v) {
  int l = LCA(u, v);
  //be careful with the next lines, this problem allowed this type of
  //updates, others may not
  lineU(u, l);
  lineU(v, l);
  lineU(l, l);
}

int size(int n, int pr) {
  sz[n] = 1;
  int lim = grafo[n].size();
  for (int i = 0; i < lim; ++i) {
    int v = grafo[n][i];
    if (v == pr) continue;
    sz[n] += size(v, n);
  }
  return sz[n];
}

void hl(int n, int pr, int grp){
  int best = -1;

  d[n] = (n ? d[pr] : 0) + 1;
  p[n][0] = pr;
  g[n] = grp;
  //barray[nIx] = nv[n]; 
  ix[n] = nIx;
  nIx++;
  
  int lim = grafo[n].size();
  for (int i = 0; i < lim; ++i) {
    int v = grafo[n][i];
    if (v == pr) continue;
    if (best == -1 || sz[best] < sz[v])
      best = v;
  }

  if (best != -1)
    hl(best, n, grp);

  for (int i = 0; i < lim; ++i) {
    int v = grafo[n][i];
    if (v == pr || v == best) continue;
    hl(v, n, v);
  }
}

int lineQ(int u, int v){
  int ans = 0;

  for (; g[u] != g[v]; u = p[g[u]][0])
    ans += query(ix[g[u]], ix[u]);

  ans += query(ix[v], ix[u]);

  return ans;
}

int treeQ(int u, int v) {
  int l = LCA(u, v);
  return lineQ(u, l) + lineQ(v, l) - lineQ(l, l);
}

void PreLCA() {
  for (int k = 1; k < MAXK; ++k)
    for (int i = 0; i < N; ++i)
      p[i][k] = p[p[i][k - 1]][k - 1];
  return;
}

int main() {
  scanf("%d", &N);
  nIx = 0;
  int lim = N - 1, u, v;
  for (int i = 0; i < lim; ++i) {
    scanf("%d%d", &u, &v);
    u--, v--;
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }
  
  size(0, 0);
  hl(0, 0, 0);
  build();
  PreLCA();
  scanf("%d", &q);
  int op;
  while (q--) {
    scanf("%d%d%d", &op, &u, &v);
    u--, v--;
    if (op == 1)
      updatetree(u, v);
    else
      printf("%d\n", treeQ(u, v));
  }
  return 0;
}
heavy_ligth.txt
Iniciar sesión
Mostrando heavy_ligth.txt.