#include <bits/stdc++.h>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

double r[82000];
double p[8200][8100];

int main(){
	int n; cin >> n;
	FOR(i,0,n) cin >> r[i];
	FOR(i,0,n) r[i] *= 2;
	double r0 = r[0]; r[0] = 0;
	int N = 1 << (32-__builtin_clz(n-1));
	sort(r,r+n);
	FOR(i,n,N) r[i] = r[i-n]-1;
	sort(r,r+N);
	// make it alternating
	int ul = 0;
	FOR(i,0,N){
		if (int(r[i]) % 2) ul++;
		else {
			if (ul > 1){
				int b = r[i];
				FOR(j,i-ul,i+ul-1)
					r[j] = ((j-(i-ul)) % 2) ? b : b-1 ;
			}
			ul = 0;
		}
	}
	
	r[0] = r0;

	FOR(i,0,N) FOR(j,0,N) p[i][j] = (i == j)?1:0;
	int b = 0, l = 0, s = 1;
	FOR(y,N,2*N-1) {
		// b ... b+s-1 (in l) vs  b+s .. b+2*s-1 in (l+1)
		FOR(i,b,b+2*s){
			p[y][i] = 0;
			int add = (i>=b+s)?0:s;
			int ia = (i>=b+s)?1:0;
			FOR(j,b+add,b+add+s){
				if (int(r[i]) % 2 || int(r[j]) % 2) p[y][i] += p[l+ia][i] * p[l+1-ia][j] * (1-(int(r[i])%2));
				else p[y][i] += p[l+ia][i] * p[l+1-ia][j] * (r[i] / (r[i] + r[j]));
			}
		}

		l+=2;
		b+=2*s;
		if (b == N) b = 0, s*=2;
	}

	cout << fixed << setprecision(10) << p[2*N-2][0] << endl;
}
