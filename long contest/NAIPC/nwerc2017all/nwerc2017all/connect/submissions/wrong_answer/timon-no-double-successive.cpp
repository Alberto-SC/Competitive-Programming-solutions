#include <bits/stdc++.h>
using namespace std;
using ld = long double;
constexpr ld EPS = 1e-9;
constexpr int R = 4, C = 4;

struct P {
	ld x, y;
	P operator+(const P &p) const { return P{x+p.x, y+p.y}; }
	P operator-(const P &p) const { return P{x-p.x, y-p.y}; }
	ld operator*(const P &p) const { return x*p.x + y*p.y; }
	P operator*(ld c) const { return P{x*c, y*c}; }
	P operator/(ld c) const { return P{x/c, y/c}; }
	void debug(string id) { cerr << id << ": " << x << ' ' << y << endl; }
};
ld det(P p1, P p2) { return p1.x*p2.y - p2.x*p1.y; }
ld det(P p1, P p2, P p3) { return det(p1 - p3, p2 - p3); }
bool onsegment(P l1, P l2, P p) {
	if (abs(det(l1, l2, p)) > EPS) return false;
	return min(l1.x, l2.x) - EPS <= p.x && p.x <= max(l1.x, l2.x) + EPS
		&& min(l1.y, l2.y) - EPS <= p.y && p.y <= max(l1.y, l2.y) + EPS;
}
bool intersect(P l1a, P l1b, P l2a, P l2b, P &res) {
	P l1ba = l1b - l1a, l2ba = l2b - l2a, v = l1a - l2a;
	ld den = det(l1ba * -1LL, l2ba);
	if (abs(den) < EPS) return false;
	ld lambda = (v * P{l2ba.y, -l2ba.x}) / den;
	res = l1a + l1ba * lambda;
	return true;
}

int main(int argc,char **argv) {
	vector<P> pts(R * C, P{0.0, 0.0});
	for (int r = 0; r < R; ++r)
		for (int c = 0, v; c < C; ++c)
			cin >> v, pts[--v] = P{ld(c), ld(R - 1 - r)};

	// Two successive colinear segments.
	for (size_t i = 1; i + 1 < pts.size(); ++i) {
		if (onsegment(pts[i], pts[i] + (pts[i]-pts[i - 1])*1000.0, pts[i+1])) {
			pts.erase(pts.begin()+i);
			--i;
			continue;
		}
	}
	
	// Neighbouring segments intersect (correctly).
	for (size_t i = 1; i + 2 < pts.size(); ++i) {
		P is;
		if (!intersect(pts[i - 1], pts[i], pts[i + 1], pts[i + 2], is))
			continue;
		if (!onsegment(pts[i], pts[i]+(pts[i]-pts[i-1])*1000.0, is)
		 || !onsegment(pts[i+1], pts[i+1]+(pts[i+1]-pts[i+2])*1000.0, is))
			continue;
		pts.erase(pts.begin()+i+1);
		pts[i] = is;
	}
	printf("%d\n", int(pts.size() - 1));
	if (argc>1) for (const P &p : pts) printf("%.10lf %.10lf\n", double(p.x), double(p.y));

	return 0;
}
