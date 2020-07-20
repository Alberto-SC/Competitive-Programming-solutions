class BIT {
	vector<int> v;
	
	int query (int i) {
		int ans = 0;
		for (; i > 0; i -= i&-i) ans += v[i];
		return ans;
	}

public:
	BIT (int n) {
		int sz = 1 << (32 - __builtin_clz (n - 1));
		v.resize(sz + 1, 0);
	}

	void update (int i, int k) {
		for (; i < v.size(); i += i&-i) v[i] += k;
	}

	int query (int i, int j) {
		return query(j) - query(i-1);
	}
};