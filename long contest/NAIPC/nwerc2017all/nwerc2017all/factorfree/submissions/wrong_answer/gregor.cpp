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

int prim[760000];
int np;


map<int,set<int> > posOfVal;

set<int> pdiv[11000000];

map<int, set<int> > pf;

bool isP[11000000];
void era(int N){
		FOR(i,0,N+1) isP[i] = true;
		np = 0;
		FOR(i,2,N+1) if (isP[i]){
				prim[np++] = i;
				FORS(j,i,N+1,i) {
						isP[j] = false;
						if (posOfVal.count(j)){
								pdiv[i].insert(all(posOfVal[j]));
								FORIT(k,posOfVal[j]) pf[*k].insert(i);
						}
				}
		}
}

int a[11000000];
int pa[11000000];
int nb[11000000];
int na[11000000];

bool solve(int x, int y, int p);

bool root(int x, int y, int i){
		if (nb[i] >= x || na[i] <= y)	return false;
		return solve(x,i-1,i+1) && solve(i+1,y,i+1);
}

bool solve(int x, int y, int p){
		if (x == y) pa[x] = p;
		if (x >= y) return true;
		FOR(i,0,(y-x)/2+1){
				if (x+i <= y){
						pa[x+i] = p;
						if (root(x,y,x+i)) return true;
				}
				if (x-i >= x){
				pa[x-i] = p;
				if (root(x,y,x-i)) return true;
				}
		}
		return false;
}

int main(){
		int n; cin >> n;
		FOR(i,0,n) cin >> a[i], posOfVal[a[i]].insert(i);
		era(10000001);
		FOR(i,0,n){
				nb[i] = -1;
				na[i] = n;
				FORIT(j,pf[i]) {
						auto k = pdiv[*j].find(i);
						if (k != pdiv[*j].begin()){
								k--;
								nb[i] = max(nb[i],*k);
								k++;
						}
						k++;
						if (k != pdiv[*j].end())
								na[i] = min(na[i],*k);
				}
		}
		if (solve(0,n-1,0)){
				FOR(i,0,n) cout << (i?" ":"") << pa[i];
				cout << endl;
		} else {
				cout << "impossible" << endl;
		}
}
