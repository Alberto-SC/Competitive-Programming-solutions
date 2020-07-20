class SegmentTree { // segtree of sum
	int sz;
	vector<long long> st, lz;

	void prop (int p, long long l, long long r) {
		st[p] += (r-l+1)*lz[p];
		if (l != r) {
			lz[2*p] += lz[p];
			lz[2*p + 1] += lz[p];
		} 
		lz[p] = 0;
	}

	long long qry (int a, int b, int p, int l, int r) {
		prop(p, l, r);
		if (l >= a and b >= r) return st[p]; // total overlap
		if (r < a or b < l)    return 0; // no overlap
		int m = (l+r)/2, nxt = 2*p; // partial overlap
		return qry(a, b, nxt, l, m) + qry(a, b, nxt+1, m+1, r); 
	}

	void upd (int a, int b, long long v, int p, int l, int r) {
	  prop(p, l, r);
		if (l >= a and b >= r) {
			lz[p] += v;
			prop(p, l, r);
		} else if (r >= a and b >= l) {
			int m = (l+r)/2, nxt = 2*p;
			upd(a, b, v, nxt, l, m);
			upd(a, b, v, nxt+1, m+1, r);
			st[p] = st[nxt] + st[nxt+1];
		}
	}

public:
	SegmentTree (int n) {
		sz = 1 << (32 - __builtin_clz (n - 1));
		st.resize(2*sz+1, 0);
		lz.resize(2*sz+1, 0);
	}

	long long qry (int a, int b) {
		return qry(a, b, 1, 1, sz);
	}
	
	void upd (int a, int b, long long v) {
		upd(a, b, v, 1, 1, sz);
	}
};
