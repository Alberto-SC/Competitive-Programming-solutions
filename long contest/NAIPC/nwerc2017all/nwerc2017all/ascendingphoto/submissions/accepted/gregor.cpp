#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cfloat>
#include <climits>
#include <numeric>
#include <iomanip>
#include <unordered_map>

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

int h[2000*1000];
unordered_map<int,vi> pp;

int main(){
		int n; cin >> n;
		set<int> s;
		map<int,int> m;
		FOR(i,0,n) cin >> h[i], s.insert(h[i]);
		FORIT(i,s) m[*i] = sz(m);
		int N = 0;
		FOR(i,0,n) {
				h[N] = m[h[i]];
				if (N && h[N] == h[N-1]) continue;
				pp[h[N]].push_back(N);
				N++;
		}

		// construct list of non-cuts for all entry <= i
		pii a(0,oo);
		pii b(0,oo);

		FOR(i,0,sz(s)){
				pii na = a;
				pii nb = b;
				FORIT(p,pp[i]){
						if (*p == N-1 || h[*p]+1 != h[*p+1]) continue;

						// try to create a solution in which we keep *this*	pair
						pii extend(1,*p);
						extend.first += (a.second + 1 != *p) ? a.first : b.first;
						if (sz(pp[i+1]) == 1) extend.second = oo;
						
						if (extend > na) nb = na, na = extend;
						else if (extend > nb) nb = extend;
				}
				a = na;
				b = nb;
		}
		cout << N - 1 - a.first << endl;
}
