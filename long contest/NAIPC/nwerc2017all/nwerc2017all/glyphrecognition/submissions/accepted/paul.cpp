#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	
	vector<int> x(n), y(n);
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
	
	int best_k = -1;
	double best_score = 0;
	for (int k = 3; k <= 8; k++) {
		double sector = 2*M_PI/k;
		double rmin = 1e100, rmax = 0;
		for (int i = 0; i < n; i++) {
			double alpha = atan2(y[i],x[i]);
			if (alpha < 0) alpha += 2*M_PI;
			while (alpha > sector) alpha -= sector;
			
			double r = hypot(x[i],y[i]) * cos(alpha - sector/2);
			rmin = min(rmin,r);
			rmax = max(rmax,r);
		}
		double score = (rmin*rmin) / (rmax*rmax);
		if (score > best_score) {
			best_k = k;
			best_score = score;
		}
		cerr << k << " " << score << endl;
	}
	cout << best_k << " " << fixed << setprecision(10) << best_score << endl;
}
