#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Angle {
	int x, y;
	int t;
	Angle(int x, int y, int t=0) : x(x), y(y), t(t) {}
	Angle operator-(Angle a) const { return {x-a.x, y-a.y, t}; }
	int quad() const {
		assert(x || y);
		if (y < 0) return (x >= 0) + 2;
		if (y > 0) return (x <= 0);
		return (x <= 0) * 2;
	}
	Angle t90() const { return {-y, x, t + (quad() == 3)}; }
	Angle t180() const { return {-x, -y, t + (quad() >= 2)}; }
	Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
	return make_tuple(a.t, a.quad(), a.y * (ll)b.x) <
	       make_tuple(b.t, b.quad(), a.x * (ll)b.y);
}
bool operator>=(Angle a, Angle b) { return !(a < b); }
bool operator>(Angle a, Angle b) { return b < a; }
bool operator<=(Angle a, Angle b) { return !(b < a); }

ostream& operator<<(ostream& os, Angle a) {
	return os << "(" << a.x << ", " << a.y << ", " << a.t << ")";
}

struct AngleRange {
	Angle from, to;
	bool incfrom, incto;
	static AngleRange ray(Angle v) {
		assert(v.t == 0);
		return {v, v, true, true};
	}
	bool inrange(Angle v) const {
		assert(v.t == 0);
		assert(from.t == 0);
		while (!(incfrom ? from <= v : from < v)) v.t++;
		return (incto ? v <= to : v < to);
	}
};

int main() {
	cin.sync_with_stdio(false);
	vector<Angle> ps;
	int W = 4;
	ps.assign(W*W, Angle{0,0});
	rep(i,0,W) rep(j,0,W) {
		int ind;
		cin >> ind;
		ps[ind-1] = Angle(i, j);
	}

	Angle last{0,0};
	AngleRange ang = AngleRange::ray(Angle{0,1});
	int res = 1, index = 0;
	trav(p, ps) {
// cerr << p.x << ' ' << p.y << endl;
		Angle v = p - last;
		if (index == 0) {
			// Nothing
		} else if (index == 1) {
			assert(v.x || v.y);
			ang = AngleRange::ray(v);
		} else {
			assert(v.x || v.y);
			if (ang.inrange(v)) {
				ang = AngleRange::ray(v);
			} else {
				res++;
// cerr << ang.from << ang.incfrom << ' ' << ang.to << ang.incto << endl;

				Angle froma = ang.from.t180();
				Angle toa = ang.to.t180();
				while (toa > v.t180()) toa.t--;
				while (froma >= v.t180()) froma.t--;
				while (toa.t180() <= v) toa.t++;
				while (froma.t180() < v) froma.t++;
				assert(froma <= toa);
				ang = AngleRange::ray(v);
				if (toa > v) {
					ang.to = toa;
					ang.incto = false;
				}
				if (froma < v) {
					ang.from = froma;
					ang.incfrom = false;
				}
				assert(ang.from.t <= 0);
				while (ang.from.t < 0) {
					ang.from.t++;
					ang.to.t++;
				}
				assert(ang.from.t == 0);
			}
		}
		last = p;
		index++;
	}
	cout << res << endl;
}
