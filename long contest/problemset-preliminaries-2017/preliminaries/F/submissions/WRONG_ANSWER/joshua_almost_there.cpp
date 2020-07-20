#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

using ld = long double;

struct pt {
	ld x, y;
};

const pt p_r = {0.5, -0.5 * sqrt(ld(3))};
const pt p_g = {0.5, +0.5 * sqrt(ld(3))};
const pt p_b = {-1, 0};

pt operator+(pt l, pt r) { return {l.x + r.x, l.y + r.y}; }
pt operator-(pt l, pt r) { return {l.x - r.x, l.y - r.y}; }
pt operator*(ld s, pt p) { return {s * p.x, s * p.y}; }
ld dot(pt l, pt r) { return l.x * r.x + l.y * r.y; }
ld length(pt p) { return hypot(p.x, p.y); }
pt rotccw(pt p) { return {-p.y, p.x}; }
pt rotcw(pt p) { return {p.y, -p.x}; }

struct circle {
	pt centre;
	ld radius;
};

istream &operator>>(istream &in, pt &p) { return in >> p.x >> p.y; }
istream &operator>>(istream &in, circle &c) { return in >> c.centre >> c.radius; }
ostream &operator<<(ostream &out, pt const &p) { return out << p.x << ' ' << p.y; }
ostream &operator<<(ostream &out, circle const &c) { return out << c.centre << ' ' << c.radius; }

// given two points, and an angle
// give a circle with with those points and a point with that angle
// returns LEFT circle first (looking from a -> b)
pair<circle, circle> circle_from(pt a, pt b, ld phi) {
	// the division for h cannot handle phi = 0
	if(phi == 0) { return {circle{{0, 0}, 0}, circle{{0, 0}, 0}}; }

	// first we comput a third point (twice)
	// which will have angle phi with a and b
	// calculated on the perp line of b-a.
	const auto diff = b - a;
	const auto y    = rotccw(diff);
	const auto m    = 0.5 * (a + b);

	const auto h  = 1 / (2.0 * tan(0.5 * phi));
	const auto p1 = m + h * y;
	const auto p2 = m - h * y;

	// clog << p1 << " and " << p2 << endl;

	// now a,b,c1 and a,b,c2 are circles
	// to compute the centre points
	// we intersect two lines
	const auto comp = [&](const pt p) {
		const auto diff2 = p - a;
		const auto m2    = 0.5 * (a + p);

		const auto xx = diff.y * dot(diff2, m2) - dot(diff, m) * diff2.y;
		const auto yy = dot(diff, m) * diff2.x - diff.x * dot(diff2, m2);
		const auto zz = diff.x * diff2.y - diff.y * diff2.x;

		// this means that the points are colinear
		// can only happen if a == b
		assert(zz != 0);
		// Not sure why I need to negate here... Shouldn't happen
		return pt{-xx / zz, -yy / zz};
	};

	const auto c1 = comp(p1);
	const auto c2 = comp(p2);

	const auto r = length(c1 - a);
	return make_pair(circle{c1, r}, circle{c2, r});
}

// returns number of intersections and the points
using T = tuple<int, pt, pt>;
T intersect(const circle c1, const circle c2) {
	const auto p1 = c1.centre, p2 = c2.centre;
	const auto r1 = c1.radius, r2 = c2.radius;

	// compute distance between centres
	const auto diff = p2 - p1;
	const auto L    = length(diff);

	// no overlap
	if(L > r1 + r2) return T{0, {}, {}};

	// containment or equality
	if(L <= abs(r1 - r2)) return T{-1, {}, {}};

	// distance to midpoint from centre 1
	const auto a = (r1 * r1 - r2 * r2 + L * L) / (2 * L);
	// mid point
	const auto m = p1 + (a / L) * diff;
	// height from mid point
	const auto h = sqrt(r1 * r1 - a * a);

	// only one intersection point if h is small, else two
	// may want to check with epsilon here
	if(h <= 0) {
		const auto ret = m;
		return T{1, ret, ret};
	} else {
		const auto ret1 = m + (h / L) * rotccw(diff);
		const auto ret2 = m - (h / L) * rotccw(diff);
		return T{2, ret1, ret2};
	}
}

struct color {
	ld r, g, b;
};

bool operator==(color c1, color c2) {
	return make_tuple(c1.r, c1.g, c1.b) == make_tuple(c2.r, c2.g, c2.b);
}

bool operator!=(color c1, color c2) { return !(c1 == c2); }

istream &operator>>(istream &in, color &c) { return in >> c.r >> c.g >> c.b; }

ostream &operator<<(ostream &out, color c) { return out << c.r << ' ' << c.g << ' ' << c.b; }

int main() {
	// number of pixels
	int n;
	cin >> n;
	assert(8 <= n && n <= 1000000);

	// viewing angle
	ld phi;
	cin >> phi;
	assert(2.0 / 8.0 * M_PI <= phi && phi <= 2.0 / 4.0 * M_PI);

	clog << "n = " << n << ", phi = " << phi << endl;

	// pixels
	vector<color> image(n);
	for(auto &c : image) {
		cin >> c;
		assert(0 <= c.r && c.r <= 1);
		assert(0 <= c.g && c.g <= 1);
		assert(0 <= c.b && c.b <= 1);
	}

	// we look where the colors are
	// note that one color can be (partly) occluded.
	using interval      = pair<int, int>;
	interval r_interval = {0, 0};
	interval g_interval = {0, 0};
	interval b_interval = {0, 0};

	int first_non_black = 0;

	const auto intlength = [](interval in) { return in.second - in.first; };

	const auto check_update = [](interval &interval, int i, ld c) {
		if(interval.first == 0 && c > 0) {
			interval.first = i;
		} else if(interval.first && interval.second == 0 && c < 1) {
			interval.second = i;
		}
	};

	for(int i = 0; i < n; ++i) {
		check_update(r_interval, i, image[i].r);
		check_update(g_interval, i, image[i].g);
		check_update(b_interval, i, image[i].b);

		if(first_non_black == 0 && (image[i].r > 0 || image[i].g > 0 || image[i].b > 0)) {
			first_non_black = i;
		}
	}

	function<bool(pt)> blue_red_test   = nullptr;
	function<bool(pt)> red_green_test  = nullptr;
	function<bool(pt)> green_blue_test = nullptr;

	if(r_interval.first && b_interval.first) {
		if(r_interval.first < b_interval.second) {
			blue_red_test = [](pt p) { return dot(p_g, p) >= 0; };
		}
		if(b_interval.first < r_interval.second) {
			blue_red_test = [](pt p) { return dot(p_g, p) <= 0; };
		}
	}
	if(g_interval.first && r_interval.first) {
		if(g_interval.first < r_interval.second) {
			red_green_test = [](pt p) { return dot(p_b, p) >= 0; };
		}
		if(r_interval.first < g_interval.second) {
			red_green_test = [](pt p) { return dot(p_b, p) <= 0; };
		}
	}
	if(b_interval.first && g_interval.first) {
		if(b_interval.first < g_interval.second) {
			green_blue_test = [](pt p) { return dot(p_r, p) >= 0; };
		}
		if(g_interval.first < b_interval.second) {
			green_blue_test = [](pt p) { return dot(p_r, p) <= 0; };
		}
	}

	// all three visitble -> one is redundant
	if(r_interval.first && g_interval.first && b_interval.first) {
		vector<interval *> v{&r_interval, &g_interval, &b_interval};
		sort(v.begin(), v.end(), [](interval *l, interval *r) { return *l < *r; });
		if(intlength(*v[0]) < intlength(*v[2])) *v[0] = interval{0, 0};
		if(intlength(*v[2]) < intlength(*v[0])) *v[2] = interval{0, 0};
		if(intlength(*v[0]) == intlength(*v[2])) {
			assert(v[0]->second == v[2]->first);
			// here a small pixel is in the middle.
			// Let's compute all possibilities?
		}
	}

	// from an interval, we can compute an angle (radians)
	const auto cphi = [&](interval const i, ld color::*component) {
		if(i.first == 0 || i.second == 0) return ld(0);

		ld s     = image[i.first].*component;
		ld e     = image[i.second].*component;
		ld total = intlength(i) - 1 + s + e;
		return phi * total / ld(n);
	};

	// for each interval, we will compute possible circles
	// all from origin to extremal point
	const auto c_r = circle_from({0, 0}, p_r, cphi(r_interval, &color::r));
	const auto c_g = circle_from({0, 0}, p_g, cphi(g_interval, &color::g));
	const auto c_b = circle_from({0, 0}, p_b, cphi(b_interval, &color::b));

	// now we will intersect the circles. Only the corresponding pairs
	// one intersection is always zero (or close to it), so we can skip it.
	vector<pt> possible_pts;
	const auto add = [&](pt p) {
		if(length(p) > 0.00001) possible_pts.push_back(p);
	};

	for(auto c : {make_pair(c_r, c_g), make_pair(c_r, c_b), make_pair(c_g, c_b)}) {
		if(c.first.first.radius == 0 || c.second.first.radius == 0) continue;

		const auto ret1 = intersect(c.first.first, c.second.second);
		add(get<1>(ret1));
		add(get<2>(ret1));
		const auto ret2 = intersect(c.first.second, c.second.first);
		add(get<1>(ret2));
		add(get<2>(ret2));
	}

	const auto clamp = [](ld rho) {
		if(rho > M_PI) return rho - 2 * M_PI;
		if(rho < -M_PI) return rho + 2 * M_PI;
		return rho;
	};

	const auto phi2 = [&]() {
		ld s     = image[first_non_black].r + image[first_non_black].g + image[first_non_black].b;
		ld total = first_non_black - s + 1;
		return phi * total / ld(n);
	}();

	// calculating the angle
	// I could've done this differently I guess
	// But it works
	for(auto p : possible_pts) {
		const auto dr    = p_r - p;
		const auto dg    = p_g - p;
		const auto db    = p_b - p;
		const auto mp    = pt{0, 0} - p;
		const auto alph0 = atan2(mp.y, mp.x);
		const auto alphr = clamp(atan2(dr.y, dr.x) - alph0);
		const auto alphg = clamp(atan2(dg.y, dg.x) - alph0);
		const auto alphb = clamp(atan2(db.y, db.x) - alph0);
		const auto e2    = max(alphr, max(alphg, alphb)) + alph0;
		const auto alpha = e2 + phi2 - 0.5 * phi;
		// clog << p << " " << alpha << endl;

		bool valid                                       = true;
		if(blue_red_test && !blue_red_test(p)) valid     = false;
		if(red_green_test && !red_green_test(p)) valid   = false;
		if(green_blue_test && !green_blue_test(p)) valid = false;
		// clog << (valid ? " valid " : "INVALID") << endl;

		if(valid) {
			cout << setprecision(10) << p << ' ' << alpha << endl;
			// return 0;
		}
	}
}
