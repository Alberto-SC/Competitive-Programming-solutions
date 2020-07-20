#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

double r[4096], a[4096], dp[4096][12];

double rec(int i, int k) {
	if (k < 0) return 1;
	if (a[i] == 0) return 0;
	if (dp[i][k] > 0) return dp[i][k];
	
	int jmin = ((i >> k) ^ 1) << k, jmax = jmin + (1 << k);

	double res = 0;
	FOR(j,jmin,jmax) res += a[i] * rec(j,k-1) / (a[i]+a[j]);
	res *= rec(i,k-1);

	return dp[i][k] = res;
}

int main() {
	int n; cin >> n;
	FOR(i,0,n) cin >> r[i];
	sort(r+1,r+n);
	
	int m = 1, k = 0;
	while (m < n) m *= 2, k++;
	
	FOR(i,0,m-n) a[2*i] = r[i];
	FOR(i,m-n,n) a[m-n+i] = r[i];
	
	cout << fixed << setprecision(20) << rec(0,k-1) << endl;
}
