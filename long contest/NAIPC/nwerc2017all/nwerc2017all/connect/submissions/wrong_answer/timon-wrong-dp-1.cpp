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
	P ortho() const { return P{-y, x}; }
	void debug(string id) const { cerr << id << ": " << x << ' ' << y << endl; }
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
bool onsegment(P p1, P p2, P p) {
	if (abs(det(p1, p2, p)) > EPS) return false;
	ld pr = project(p1, p2, p);
	return -EPS < pr && pr < 1.0 + EPS;
}
bool intersect(P l1a, P l1b, P l2a, P l2b, P &res) {
	P l1ba = l1b - l1a, l2ba = l2b - l2a, v = l1a - l2a;
	ld den = det(l1ba * -1LL, l2ba);
	if (abs(den) < EPS) return false;
	ld lambda = (v * P{l2ba.y, -l2ba.x}) / den;
	res = l1a + l1ba * lambda;
	return true;
}

// Extend a with lines throug p[l..r]. Tries to end with a line through p[r-1]
// and p[r].
bool extend(vector<P> &a, vector<P> &p, size_t l, size_t r) {
	int sz = (int)a.size();

	// Special case for adding a single point. Just run a line from the last
	// point of a to p[l], possibly deleting an intermediate colinear point.
	if (l == r) {
		if (onsegment(a[sz-2], p[l], a[sz-1]))
			a.pop_back();
		a.push_back(p[l]);
		return true;
	}

	// Special case for adding two points, just try intersecting a line through
	// them with the last line.
	if (l + 1 == r) {
		P np;
		if (!intersect(a[sz-2], a[sz-1], p[l], p[r], np)) return false;
		if (!onhalfline(a[sz-1], a[sz-1] - a[sz-2], np)) return false;
		if (!onhalfline(p[l], p[l] - p[r], np)) return false;
		a.pop_back();
		a.push_back(np);
		a.push_back(p[r]);
		return true;
	}

	// A finishes with the half-line a[sz-2] -> a[sz] -> -> ->
	// We now try to extend it through points p[l], p[l+1], ..., p[r],
	// Trying to end with the line -> -> -> p[r-1] -> p[r].

	vector<P> dir(r - l - 1, {0, 0});
	for (size_t i = l; i + 2 <= r; ++i) {
		P dir1 = {0, 0}, dir2 = {0, 0};
		if (l == i) {
			dir1 = a[sz-1] - a[sz-2];
		} else {
			dir1 = p[i] - p[i-1];
			// Rotate until away from p[i] to p[i+1].
			dir1 = dir1.ortho();
			if (project(p[i], p[i+1], p[i] + dir1) > -EPS)
				dir1 = dir1 * (-1);
		}
		dir1 = dir1 / sqrt(dir1.lsq());
		if (i + 2 == r) {
			dir2 = p[r-1] - p[r];
		} else {
			dir2 = p[i] - p[i+1];
			// Rotate until away from p[i] to p[i-1]
			dir2 = dir2.ortho();
			P pr = (l < i ? p[i-1] : a.back());
			if (project(p[i], pr, p[i] + dir2) > -EPS)
				dir2 = dir2 * (-1);
		}
		dir2 = dir2 / sqrt(dir2.lsq());
		P normal = (dir1 + dir2);
		normal = normal / sqrt(normal.lsq());
		dir[i - l] = normal.ortho();
	}

	vector<P> intermediate;
	{
		P np;
		if (!intersect(a[sz-2], a[sz-1], p[l], p[l] + dir[0], np))
			return false;
		if (!onhalfline(a[sz-1], a[sz-1] - a[sz-2], np))
			return false;
		intermediate.push_back(np);
	}
	for (size_t i = 1; i < dir.size(); ++i) {
		P np;
		if (!intersect(intermediate.back(), p[l+i-1],
				p[l+i], p[l+i] + dir[i], np))
			return false;
		if (!onsegment(intermediate.back(), np, p[l+i-1]))
			return false;
		intermediate.push_back(np);
	}
	{
		P np;
		if (!intersect(intermediate.back(), p[r-2], p[r-1], p[r], np))
			return false;
		if (!onsegment(intermediate.back(), np, p[r-2]))
			return false;
		if (!onsegment(np, p[r], p[r-1]))
			return false;
		intermediate.push_back(np);
	}

	a.pop_back();
	for (const auto &pt : intermediate) a.push_back(pt);
	a.push_back(p[r]);
	return true;
}

int main(int argc,char **argv) {
	vector<P> pts(R * C, P{0.0, 0.0});
	for (int r = 0; r < R; ++r)
		for (int c = 0, v; c < C; ++c)
			cin >> v, pts[--v] = P{ld(c), ld(R - 1 - r)};

	// dp[i] contains a sequence of lines through points 0..i+1.
	vector<vector<P>> dp(pts.size()-1);
	dp[0].push_back(pts[0]);
	dp[0].push_back(pts[1]);

	for (size_t i = 1; i < pts.size() - 1; ++i) {
		for (size_t p = 0; p < i; ++p) {
			vector<P> attempt(dp[p]);
			if (extend(attempt, pts, p+2, i+1)) {
				if (attempt.size() < dp[i].size() || dp[i].empty()) {
					swap(attempt, dp[i]);
				}
			}
		}
	}

	// Current implementation might result in colinear points, remove.
	for (int i = (int)pts.size() - 2; i > 0; --i)
		if (onsegment(pts[i-1], pts[i+1], pts[i]))
			pts.erase(pts.begin()+i);

	printf("%d\n", int(dp.back().size() - 1));
	if (argc>1) for (const P &p : dp.back()) printf("%.10lf %.10lf\n", double(p.x), double(p.y));

	return 0;
}
