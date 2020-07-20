#include <bits/stdc++.h>
using namespace std;
struct Node {
    int sum, leftId, rightId;
    Node(int low, int high, int idl = -1, int idr = -1)
        : sum(high-low+1), leftId(idl), rightId(idr)
    {}
};
 
struct SegmentTree {
    const int left, right;
    vector<Node> tree;
    void extend(int id, int l, int r) {
        // Check on estimated max size
        assert(tree.size() <= (1u << 21) + (1u << 20));
        if (tree[id].leftId == -1) {
            int mid = (l + r) >> 1;
            tree.push_back(Node(l, mid));
            tree[id].leftId = (int)tree.size()-1;
            tree.push_back(Node(mid+1, r));
            tree[id].rightId = (int)tree.size()-1;
        }
    }
 
    void update(int index, int delta, int id, int l, int r) {
        if (index < l || index > r) {
            return;
        }
 
        if (l == r) {
            tree[id].sum += delta;
            return;
        }
 
        extend(id, l, r);
 
        const int idl = tree[id].leftId;  assert(idl != -1);
        const int idr = tree[id].rightId; assert(idr != -1);        
        const int m = (l+r)/2;
 
        update(index, delta, idl,   l, m);
        update(index, delta, idr, m+1, r);
 
        tree[id].sum = tree[idl].sum + tree[idr].sum;
    }
 
    void update(int index, int delta) {
        return update(index, delta, 0, left, right);
    }
 
    int query(int k, int id, int l, int r) {
        if (l == r) {
            return l;
        }
 
        extend(id, l, r);
 
        const int idl = tree[id].leftId;  assert(idl != -1);
        const int idr = tree[id].rightId; assert(idr != -1);        
        const int m = (l+r)/2;
 
        if (tree[idl].sum >= k) {
            return query(k, idl, l, m);
        } else {
            return query(k - tree[idl].sum, idr, m+1, r);
        }
    }
 
    int query(int k) {
        return query(k, 0, left, right);
    }
 
    SegmentTree(int l, int r) : left(l), right(r) {
        tree.reserve((1u << 21) + (1u << 20)); // Reserve estimated max size Nodes
        tree.push_back(Node(l, r));
    }
};
 
int main() {
    int n, m, num;
    char op;
    scanf("%d%d", &n, &m); 
    SegmentTree st(1, n);
    for (int i = 1; i <= m; i++) {
        scanf(" %c %d", &op, &num);m                   
        int q = st.query(num);
        if (op == 'L') {
            printf("%d\n", q);
        } else {
            st.update(q, -1);
        }
    }
    return 0;
}