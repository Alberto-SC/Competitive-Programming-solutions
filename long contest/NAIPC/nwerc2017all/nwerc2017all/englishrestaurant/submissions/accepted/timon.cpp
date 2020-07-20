#include <bits/stdc++.h>
using namespace std;

using ld = long double;

int n2(int n) { return n * (n + 1) / 2; }

void fadd(ld &a, ld &b, ld p, ld q) {
	a = a*q+b*p;
	b = b*q;
}

pair<int, int> rfrac(int l, int r, const vector<int> &c, int g) {
	int lb = min(g, l > 0 ? c[l - 1] : 0);
	int rb = min(g, c[r]);
	return {c[r] <= 211 ? n2(rb) - n2(lb) : 0, rb - lb};
}

int main() {
	int n, g, t;
	cin >> n >> g >> t;
	vector<int> c(n);
	for (int &v : c) cin >> v;
	sort(c.begin(), c.end());
	for (int i = 0; i < t; ++i) c.push_back(300), ++n;

	ld nCk[212][212];
	for (int i = 0; i <= 211; ++i) nCk[0][i] = 0, nCk[i][0] = 1;
	for (int i = 1; i <= 211; ++i)
		for (int j = 1; j <= 211; ++j)
			nCk[i][j] = nCk[i-1][j-1] + nCk[i-1][j];

	// num[i][j] / den[i][j] = E(guests | group sizes in (c[i-1], c[j]] ).
	ld num[211][211], den[211][211];
	for (int r = 0; r < n; ++r) {
		tie(num[r][r], den[r][r]) = rfrac(r, r, c, g);

		for (int l = r - 1; l >= 0; --l) {
			num[l][r] = 0;
			den[l][r] = 0;
			for (int k = l; k <= r; ++k) {
				ld sum = 0.0;
				ld ways = nCk[r-l][k-l];
				// Place k.
				ld a, b;
				tie(a, b) = rfrac(l, k, c, g);
				fadd(sum, ways, a, b);

				// Place <k.
				if (l < k) fadd(sum, ways, num[l][k-1], den[l][k-1]);

				// Place >k.
				if (k < r) fadd(sum, ways, num[k+1][r], den[k+1][r]);

				num[l][r] += sum;
				den[l][r] += ways;
			}
		}
	}

	// dp[groups [i..t)][tables [j..n)] with table j used
	ld dpn[211][211], dpd[211][211];
	for (int i = 0; i < 211; ++i)
		for (int j = 0; j < 211; ++j)
			dpn[i][j] = dpd[i][j] = 0;

	// Begin by computing suffixes including people that are sent away.
	for (int i = t - 1; i >= 0; --i) {
		for (int j = n - 1; j >= 0; --j) {
			// We have t-i groups and n-j tables.
			if (t-i <= n-j) {
				dpn[i][j] = num[j][j+t-i-1];
				dpd[i][j] = den[j][j+t-i-1];
			}
		}
	}

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
		}
	}

	// Loop over the smallest table to be seated, and the last group to be
	// seated.
	ld ansn = 0.0, ansd = 0.0;
	for (int l = 0; l < n; ++l)
		ansn += dpn[0][l], ansd += dpd[0][l];
	cerr << ansn << " / " << ansd << endl;
	printf("%.12lf\n", double(ansn / ansd));

	return 0;
}
