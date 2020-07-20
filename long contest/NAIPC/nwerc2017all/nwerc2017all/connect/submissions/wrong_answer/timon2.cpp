#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Linear solution using constant extra space.

struct P {
	ll x, y;
	P operator-(const P &o) const { return P{x-o.x, y-o.y}; }
	ll operator*(const P &o) const { return x*o.x + y*o.y; }
	ll operator/(const P &o) const { return x*o.y - y*o.x; }
	P operator*(ll c) const { return P{x*c, y*c}; }
	friend ostream &operator<<(ostream &os, const P &p) {
		os << '(' << p.x << ',' << p.y << ')';
		return os;
	}
};

// Represents a pie slice!
struct C {
	bool all; // Whether C is all of R^2.
	P l, r; // If not, we include everything between l and r.
	bool lo, ro; // Whether l/r are open/closed.
	C(bool all) : all(all), l(P{0, 0}), r(P{0, 0}), lo(false), ro(false) { }
	C(P l, P r, bool lo, bool ro) : all(false), l(l), r(r), lo(lo), ro(ro) { }
	friend ostream &operator<<(ostream &os, const C &p) {
		os << '(' << p.all << ',' << p.l << ',' << p.r << ',' << p.lo << ','
			<< p.ro << ')';
		return os;
	}
};

// <0 cw =0 colinear >0 ccw
int orient(const P &l, const P &r) {
	ll c = l / r;
	return c == 0LL ? 0LL : (c > 0LL ? 1LL : -1LL);
}

// Whether point x is in pie slice p.
bool inpie(C p, P x) {
	if (p.all) return true;
	int type = orient(p.l, p.r), lo = orient(p.l, x), ro = orient(x, p.r);
	bool ilhp = lo < 0 || (lo == 0 && !p.lo),
		 irhp = ro < 0 || (ro == 0 && !p.ro);
	if (type == 0) {
		if (p.l * p.r > 0) {
			return ilhp && irhp && p.l * x >= 0 && !p.lo && !p.ro;
		} else {
			return (p.l * x >= 0 && ilhp) || (p.r * x >= 0 && irhp);
		}
	} else if (type < 0) {
		return ilhp && irhp;
	} else {
		return ilhp || irhp;
	}
}

// Get the next pie, provided x is outside p. That is, suppose we start a ray
// in some point inside pie p, through point x, then the returned pie basically
// gives all places that ray could end after going through x.
C getpie(C p, P x) {
	int lo = orient(p.l, x), ro = orient(x, p.r);
	bool ilhp = lo < 0 || (lo == 0 && !p.lo),
		 irhp = ro < 0 || (ro == 0 && !p.ro);
	if (!ilhp && !irhp) {
		return C(p.l*-1, p.r*-1, true, true);
	} else if (ilhp && !irhp) {
		return C(x, p.r*-1, false, true);
	} else if (!ilhp && irhp) {
		return C(p.l*-1, x, true, false);
	} else if (ilhp && irhp) {
		return C(p.l*-1, p.r*-1, false, false);
	}
}

constexpr int rows = 4, cols = 4;
int main() {
	vector<P> pts(rows * cols);
	for (int y = cols - 1; y >= 0; --y)
		for (int x = 0, v; x < rows; ++x)
			cin >> v, pts[v - 1] = P{x, y};

	int lines = 1;
	C p(/*all=*/true);
	for (int i = 1; i < rows * cols; ++i) {
		P dp = pts[i] - pts[i-1];
		if (inpie(p, dp)) {
			p = C(dp, dp, false, false);
		} else {
			p = getpie(p, dp);
			++lines;
		}
//		cerr << i+1 << ' ' << lines << ' ' << p << endl;
	}

	cout << lines << endl;
	return 0;
}
