#include <bits/stdc++.h>
using namespace std;

using ld = long double;

int n2(int n) { return n * (n + 1) / 2; }

void fadd(ld &a, ld &b, ld p, ld q) {
	a = a*q+b*p;
	b = b*q;
}

int main() {
	int n, g, t;
	cin >> n >> g >> t;
	vector<int> c(n);
	for (int &v : c) cin >> v;
	sort(c.begin(), c.end());

	ld nCk[101][101];
	for (int i = 0; i <= 100; ++i) nCk[0][i] = 0, nCk[i][0] = 1;
	for (int i = 1; i <= 100; ++i)
		for (int j = 1; j <= 100; ++j)
			nCk[i][j] = nCk[i-1][j-1] + nCk[i-1][j];

	// num[i][j] / den[i][j] = E(guests | group sizes in (c[i-1], c[j]] ).
	ld num[100][100], den[100][100];
	for (int r = 0; r < n; ++r) {
		num[r][r] = n2(min(g, c[r])) - (r > 0 ? n2(c[r-1]) : 0);
		den[r][r] = min(g, c[r]) - (r > 0 ? c[r-1] : 0);

			cerr << "[" << r << ", " << r << "]: ";
			cerr << num[r][r] << " / " << den[r][r] << endl;
		for (int l = r - 1; l >= 0; --l) {
			num[l][r] = 0;
			den[l][r] = 0;
			cerr << "Computing [" << l << ", " << r << "]" << endl;
			for (int k = l; k <= r; ++k) {
				cerr << " Computing " << k << endl;
				ld sum = 0.0;
				ld ways = nCk[r-l][k-l];
				cerr << "  " << sum << " / " << ways << endl;
				// Place k.
				fadd(sum, ways,
					n2(min(g, c[k])) - (l > 0 ? n2(c[l-1]) : 0),
					min(g, c[k]) - (l > 0 ? c[l-1] : 0));

				cerr << "  " << sum << " / " << ways << endl;
				// Place <k.
				if (l < k) fadd(sum, ways, num[l][k-1], den[l][k-1]);

				cerr << "  " << sum << " / " << ways << endl;
				if (k < r) fadd(sum, ways, num[k+1][r], den[k+1][r]);

				cerr << "  " << sum << " / " << ways << endl;
				num[l][r] += sum;
				den[l][r] += ways;
				cerr << ' ' << l << ' ' << r << ' ' << k << endl;
				cerr << " adding " << sum << ' ' << ways << endl;
			}
			cerr << "[" << l << ", " << r << "]: ";
			cerr << num[l][r] << " / " << den[l][r] << endl;
		}
	}

	cerr << endl << endl;

	// dp[groups [i..t)][tables [j..n)] with table j used
	ld dpn[100][100], dpd[100][100];
	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
			dpn[i][j] = dpd[i][j] = 0;

	// Begin by computing suffixes including people that are sent away.
	for (int i = t - 1; i >= 0; --i) {
		for (int j = n - 1; j >= 0; --j) {
			// We have t-i groups and n-j tables.
			if (t-i <= n-j) {
				// Suffix?
				dpn[i][j] = num[j][j+t-i-1];
				dpd[i][j] = den[j][j+t-i-1];
			} else /* (t-i > n-j) */ {
				// Send someone away?
				dpn[i][j] = dpn[i+1][j];
				dpd[i][j] = dpd[i+1][j];
				fadd(dpn[i][j], dpd[i][j], 0,
					min(g, c[n-1]) - (j > 0 ? c[j-1] : 0));
			}
			cerr << "dp["<< i << "][" << j << "] = ";
			cerr << dpn[i][j] << " / " << dpd[i][j] << endl;
		}
	}

	cerr << endl << endl;

	// Add more segments.
	for (int i = t - 1; i >= 0; --i) {
		for (int j = n - 1; j >= 0; --j) {
			for (int ni = i + 1; ni < t; ++ni) {
				for (int ns = j + (ni-i) + 1; ns < n; ++ns) {
					ld sum = 0.0, ways = nCk[t-i][t-ni];
					fadd(sum, ways, num[j][j+(ni-i)-1], den[j][j+(ni-i)-1]);
					fadd(sum, ways, dpn[ni][ns], dpd[ni][ns]);
					dpn[i][j] += sum;
					dpd[i][j] += ways;
				}
			}
			cerr << "dp["<< i << "][" << j << "] = ";
			cerr << dpn[i][j] << " / " << dpd[i][j] << endl;
		}
	}

	ld ansn = 0.0, ansd = 1.0;
	for (int l = 0; l < n; ++l)
		if (dpd[0][l] > 0)
			ansn += dpn[0][l], ansd += dpd[0][l];
	cerr << ansn << " / " << ansd << endl;
	printf("%.12lf\n", double(ansn / ansd));

	return 0;
}
