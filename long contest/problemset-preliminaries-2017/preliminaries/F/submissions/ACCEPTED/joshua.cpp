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

		// this means that the points a,b,p are colinear
		// can only happen if a == b
		assert(abs(zz) > 0.0001);
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
	if(L > r1 + r2) return T{0, pt{}, pt{}};

	// containment or equality
	if(L <= abs(r1 - r2) + 0.0000001) return T{-1, pt{}, pt{}};

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

using interval = pair<ld, ld>;
ld length(interval i) { return i.second - i.first; };

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
	vector<ld> r_pixels(n);
	vector<ld> g_pixels(n);
	vector<ld> b_pixels(n);
	for(int i = 0; i < n; ++i) { cin >> r_pixels[i] >> g_pixels[i] >> b_pixels[i]; }

	// we look where the colors are
	// note that one color can be (partly) occluded.
	interval r_interval = {0, 0};
	interval g_interval = {0, 0};
	interval b_interval = {0, 0};

	int first_non_black = 0;

	const auto check_update = [](interval &interval, int i, ld c) {
		if(interval.first == 0 && c > 0) {
			interval.first = i + (1 - c);
		} else if(interval.first > 0 && interval.second == 0 && c < 1) {
			interval.second = i + c;
		}
	};

	for(int i = 0; i < n; ++i) {
		check_update(r_interval, i, r_pixels[i]);
		check_update(g_interval, i, g_pixels[i]);
		check_update(b_interval, i, b_pixels[i]);

		if(first_non_black == 0 && (r_pixels[i] > 0 || g_pixels[i] > 0 || b_pixels[i] > 0)) {
			first_non_black = i;
		}
	}

	for(auto ip : {&r_interval, &g_interval, &b_interval}) {
		clog << '[' << ip->first << ' ' << ip->second << "] ";
	}
	clog << endl;

	// interval of size 1 are not yet on the right place
	if(r_interval.first > 0 && g_interval.first > 0 && b_interval.first > 0) {
		for(auto intp : {&r_interval, &g_interval, &b_interval}) {
			interval &intvl = *intp;
			// not really a for loop, has unique thing in it
			if(length(intvl) < 1) {
				clog << "fixup: " << intvl.first << " - " << intvl.second << endl;
				for(auto otherp :
				    {make_pair(&r_interval, &g_interval), make_pair(&g_interval, &b_interval),
				     make_pair(&b_interval, &r_interval)}) {
					if(intp == otherp.first || intp == otherp.second) continue;

					interval &min_interval = otherp.first->second > otherp.second->first
					                             ? *otherp.second
					                             : *otherp.first;
					interval &max_interval = otherp.first->second > otherp.second->first
					                             ? *otherp.first
					                             : *otherp.second;
					if(intvl.first < min_interval.second) {
						clog << "LEFT" << endl;
						intvl.first -= intvl.second - min_interval.first;
						intvl.second -= intvl.second - min_interval.first;
					} else if(intvl.second > max_interval.first + 1) {
						clog << "RIGHT" << endl;
						intvl.second += max_interval.second - intvl.first;
						intvl.first += max_interval.second - intvl.first;
					} else {
						clog << "MID" << endl;
						intvl.first  = min_interval.second;
						intvl.second = max_interval.first;
					}
				}
			}
		}
	}

	// My solution generates multiple candidates for the coordiantes
	// Then it uses the functions below to check which is the right one
	// All test works like this:
	// "If blue is left of red, the dot product with the green arrow is < 0"
	function<bool(pt)> blue_red_test   = nullptr;
	function<bool(pt)> red_green_test  = nullptr;
	function<bool(pt)> green_blue_test = nullptr;

	if(r_interval.first > 0 && b_interval.first > 0) {
		if(r_interval.first < b_interval.second) {
			blue_red_test = [](pt p) { return dot(p_g, p) >= 0; };
		}
		if(b_interval.first < r_interval.second) {
			blue_red_test = [](pt p) { return dot(p_g, p) <= 0; };
		}
	}
	if(g_interval.first > 0 && r_interval.first > 0) {
		if(g_interval.first < r_interval.second) {
			red_green_test = [](pt p) { return dot(p_b, p) >= 0; };
		}
		if(r_interval.first < g_interval.second) {
			red_green_test = [](pt p) { return dot(p_b, p) <= 0; };
		}
	}
	if(b_interval.first > 0 && g_interval.first > 0) {
		if(b_interval.first < g_interval.second) {
			green_blue_test = [](pt p) { return dot(p_r, p) >= 0; };
		}
		if(g_interval.first < b_interval.second) {
			green_blue_test = [](pt p) { return dot(p_r, p) <= 0; };
		}
	}

	// all three visitble -> one interval is not big enough (left or right)
	// when only two visible, we can't use that info
	// we actually ignore the middle part, we only need two
	// So what I said earlier is a lie: we only get 1 potential point
	// The reason is: the overlapping intervals are going in the wrong direction?
	// i.e. the function circle_from depends on the sign of angle...
	// So taking the ones in the same direction makes things consistent.
	if(r_interval.first > 0 && g_interval.first > 0 && b_interval.first > 0) {
		vector<interval *> v{&r_interval, &g_interval, &b_interval};
		sort(v.begin(), v.end(), [](interval *l, interval *r) { return *l < *r; });

		// left part is shorter, and occluded
		if(length(*v[0]) < length(*v[2])) v[0]->second = v[2]->first;
		// right is shorter hence occluded
		else if(length(*v[2]) < length(*v[0]))
			v[2]->first = v[0]->second;

		*v[1] = interval{0, 0}; // get rid of the middle guy
	}

	// from an interval, we can compute an angle (radians)
	const auto cphi = [&](interval const i) {
		if(i.first == 0 || i.second == 0) return ld(0);
		return phi * length(i) / ld(n);
	};

	// for each interval, we will compute possible circles
	// all from origin to extremal point
	const auto c_r = circle_from({0, 0}, p_r, cphi(r_interval));
	const auto c_g = circle_from({0, 0}, p_g, cphi(g_interval));
	const auto c_b = circle_from({0, 0}, p_b, cphi(b_interval));

	// now we will intersect the circles. Only the corresponding pairs
	// one intersection is always zero (or close to it), so we can skip it.
	vector<pt> possible_pts;
	const auto add = [&](pt p) {
		if(length(p) > 0.00001) possible_pts.push_back(p);
	};

	for(auto c : {make_pair(c_r, c_g), make_pair(c_b, c_r), make_pair(c_g, c_b)}) {
		if(c.first.first.radius == 0 || c.second.first.radius == 0) continue;

		{
			const auto ret = intersect(c.first.first, c.second.second);
			if(get<0>(ret) == 2) {
				add(get<1>(ret));
				add(get<2>(ret));
			} else {
				// edge case: two circles overlap. This can happen in one of the cases
				// which we can spell out
				if(dot(c.first.first.centre, p_r) < -0.5) possible_pts.push_back(-2 * p_r);
				if(dot(c.first.first.centre, p_g) < -0.5) possible_pts.push_back(-2 * p_g);
				if(dot(c.first.first.centre, p_b) < -0.5) possible_pts.push_back(-2 * p_b);
			}
		}
		{
			const auto ret = intersect(c.first.second, c.second.first);
			if(get<0>(ret) == 2) {
				add(get<1>(ret));
				add(get<2>(ret));
			} else {
				// edge case: two circles overlap. This can happen in one of the cases
				// which we can spell out
				if(dot(c.first.second.centre, p_r) < -0.1) possible_pts.push_back(-2 * p_r);
				if(dot(c.first.second.centre, p_g) < -0.1) possible_pts.push_back(-2 * p_g);
				if(dot(c.first.second.centre, p_b) < -0.1) possible_pts.push_back(-2 * p_b);
			}
		}
	}

	const auto clamp = [](ld rho) {
		if(rho > M_PI) return rho - 2 * M_PI;
		if(rho < -M_PI) return rho + 2 * M_PI;
		return rho;
	};

	const auto phi2 = [&]() {
		ld s = r_pixels[first_non_black] + g_pixels[first_non_black] + b_pixels[first_non_black];
		ld total = first_non_black - s + 1;
		return phi * total / ld(n);
	}();

	// calculating the angle
	// I could've done this differently I guess
	// But it works
	clog << possible_pts.size() << endl;
	clog << setprecision(10);
	cout << setprecision(10);
	int count = 0;
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

		bool valid                                       = true;
		if(blue_red_test && !blue_red_test(p)) valid     = false;
		if(red_green_test && !red_green_test(p)) valid   = false;
		if(green_blue_test && !green_blue_test(p)) valid = false;

		if(valid) {
			cout << p << ' ' << alpha << endl;
			count++;
			// return 0;
		} else {
			clog << "invalid: " << p << ' ' << alpha << endl;
		}
	}

	// Should be the case
	assert(count == 1);
}
