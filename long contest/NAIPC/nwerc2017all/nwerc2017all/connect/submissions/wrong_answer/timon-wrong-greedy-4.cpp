#include <bits/stdc++.h>
using namespace std;
using ld = long double;
constexpr ld EPS = 1e-9;
constexpr int R = 4, C = 4;

// Greedy, currently runs in O(n^2) because I was lazy, easily optimizable to
// O(n).
// The only thing I'm a bit worried about is going out of bounds.

struct P {
	ld x, y;
	P operator+(const P &p) const { return P{x+p.x, y+p.y}; }
	P operator-(const P &p) const { return P{x-p.x, y-p.y}; }
	ld operator*(const P &p) const { return x*p.x + y*p.y; }
	P operator*(ld c) const { return P{x*c, y*c}; }
	P operator/(ld c) const { return P{x/c, y/c}; }
	ld lsq() { return (*this)*(*this); }
	void debug(string id) { cerr << id << ": " << x << ' ' << y << endl; }
};
ld det(P p1, P p2) { return p1.x*p2.y - p2.x*p1.y; }
ld det(P p1, P p2, P p3) { return det(p1 - p3, p2 - p3); }
// Gives lambda.
ld project(P l1, P l2, P p) {
	P u = l2 - l1;
	return (u * (p - l1)) / u.lsq();
}
bool onhalfline(P s, P d, P p) {
	if (abs(det(s, s + d, p)) > EPS) return false;
	return project(s, s + d, p) > -EPS;
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

	for (size_t i = 1; i + 1 < pts.size(); ++i) {
		// Two successive colinear segments.
		if (onhalfline(pts[i], pts[i] - pts[i-1], pts[i+1])) {
			pts.erase(pts.begin()+i);
			--i;
			continue;
		}
		// Neighbouring segments intersect (correctly).
		if (i + 2 < pts.size()) {
			P is;
			if (intersect(pts[i - 1], pts[i], pts[i + 1], pts[i + 2], is)
			 && onhalfline(pts[i], pts[i] - pts[i-1], is)
			 && onhalfline(pts[i+1], pts[i+1] - pts[i+2], is)) {
				pts.erase(pts.begin()+i+1);
				pts[i] = is;
				continue;
			}
		}
		// Delete two successive segments
		if (i + 3 < pts.size()) {
			ld d1 = det(pts[i-1], pts[i], pts[i+1]);
			ld d2 = det(pts[i], pts[i+1], pts[i+2]);
			ld d3 = det(pts[i+1], pts[i+2], pts[i+3]);
			if (!((d1 > 0 && d2 > 0 && d3 > 0)
					|| (d1 < 0 && d2 < 0 && d3 < 0)))
				continue;

			// Check if this is possible.
			P displ1 = pts[i] - pts[i-1];
			P displ2 = pts[i+2] - pts[i+3];
			ld dd = det(displ1, displ2);
			if (!((dd > 0 && d1 > 0) || (dd < 0 && d1 < 0)))
				continue;

			// We need a line through P_i+1 which also hits:
			//  The line through P_i-1 and P_i, on the P_i side.
			//	The line through P_i+2 and P_i+3, on the P_i+2 side.
			// Picking e.g. the line parallel to P_i --> P_i+2 is not enough,
			// since this line may be parallel to one of the above two lines.
			// Thus, we average displ1 and displ2, and treat this as a normal
			// vector of the line we seek.
			displ1 = displ1 / sqrt(displ1.lsq());
			displ2 = displ2 / sqrt(displ2.lsq());
			P normal = (displ1 + displ2);
			normal = normal / sqrt(normal.lsq());
			// Rotate the normal for directional vector.
			P displ = {-normal.y, normal.x};

			P p1, p2;
			if (!intersect(pts[i+1], pts[i+1]+displ, pts[i-1], pts[i], p1)
			 || !intersect(pts[i+1], pts[i+1]+displ, pts[i+2], pts[i+3], p2))
				continue;
			if (!onhalfline(pts[i], pts[i] - pts[i-1], p1)
			 || !onhalfline(pts[i+2], pts[i+2]-pts[i+3], p2))
				continue;
			pts[i] = p1;
			pts[i+1] = p2;
			pts.erase(pts.begin()+i+2);
			++i;
		}
	}

	printf("%d\n", int(pts.size() - 1));
	if (argc>1) for (const P &p : pts) printf("%.10lf %.10lf\n", double(p.x), double(p.y));

	return 0;
}
