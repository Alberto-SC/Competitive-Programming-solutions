#include <bits/stdc++.h>
using namespace std;

const int X = 1e6;

double sector;

double factor(double alpha) {
	if (alpha < 0) alpha += 2*M_PI;
	while (alpha > sector) alpha -= sector;
	return cos(alpha - sector/2) / cos(sector/2);
}

double polygon_radius(double x, double y) {
	return hypot(x,y) * factor(atan2(y,x));
}

random_device rd;
mt19937_64 gen(rd());
uniform_real_distribution<double> dis(0,1);

double get_random(double a, double b) { return a + dis(gen)*(b-a); }

int main() {
	int k; cin >> k;
	int n = get_random(1,1001);
	double rmin; cin >> rmin;
	rmin *= get_random(0.7,1.3);
	double rmax = rmin * get_random(1,2);
	
	cerr << fixed << setprecision(0);
	cerr << k << "-" << n << "-" << rmin << "-" << rmax << endl;

	sector = 2*M_PI/k;

	set<pair<int,int>> s;
	while (n--) {
		int x, y, cnt = 1000;
		while (cnt --> 0) {
			double alpha = get_random(0,2*M_PI);
			double r = get_random(rmin,rmax) / factor(alpha);
			x = r*cos(alpha), y = r*sin(alpha);
			if (abs(x) > X || abs(y) > X || s.count({x,y})) continue;
			r = polygon_radius(x,y);
			if (r >= rmin && r <= rmax) break;
		}
		s.insert({x,y});
	}

	cout << s.size() << endl;
	vector<pair<int,int>> v(begin(s),end(s));
	shuffle(begin(v),end(v),gen);
	for (auto p: v) cout << p.first << " " << p.second << endl;
}
