#include <bits/stdc++.h>
using namespace std;

struct point {
	double x, y;
};

const double eps = 1e-9;

int ccw(point a, point b, point c) {
	double cross = (b.x-a.x)*(c.y-b.y) - (c.x-b.x)*(b.y-a.y);
	return abs(cross) > eps ? (cross > 0 ? 1 : -1) : 0;
}

bool point_in_polygon(vector<point> &poly, point a) {
	int winding = 0;
	for (int i = 0; i < poly.size(); i++) {
		point p = poly[i], q = poly[(i+1) % poly.size()];
		
		if (p.y < a.y + eps) {
			if (q.y > a.y + eps && ccw(p,q,a) > 0) winding++;
		} else {
			if (q.y < a.y + eps && ccw(p,q,a) < 0) winding--;
		}
	}
	assert(abs(winding) <= 1);
	return winding;
}

int main() {
	int n; cin >> n;

	vector<point> a(n);
	for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
	
	auto binary_search = [&](int k, bool is_outer) {
		double rmin = 0, rmax = 5e6;
		for (int t = 0; t < 100; t++) {
			double r = (rmin+rmax)/2;
			
			vector<point> poly(k);
			for (int i = 0; i < k; i++) poly[i] = {r*cos(i*2*M_PI/k), r*sin(i*2*M_PI/k)};
			
			int inside_cnt = 0;
			for (int i = 0; i < n; i++) inside_cnt += point_in_polygon(poly,a[i]);
			
			if (is_outer) {
				if (inside_cnt == n) rmax = r; else rmin = r;
			} else {
				if (inside_cnt == 0) rmin = r; else rmax = r;
			}
		}
		return rmin;
	};

	int best_k = -1;
	double best_score = 0;
	for (int k = 3; k <= 8; k++) {
		double rmin = binary_search(k, false), rmax = binary_search(k, true);
		
		double score = (rmin*rmin) / (rmax*rmax);
		if (score > best_score) {
			best_k = k;
			best_score = score;
		}
		cerr << k << " " << score << endl;
	}
	cout << best_k << " " << fixed << setprecision(10) << best_score << endl;
}

