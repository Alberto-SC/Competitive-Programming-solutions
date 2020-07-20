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

ll sc[3];

int main(){
	int tc; cin >> tc;
	while (tc-->0){	
		FOR(i,0,3) cin >> sc[i];
		ll d; cin >> d;

		while(d){
			sort(sc,sc+3);
			ll minInc = ((sc[0] != sc[1])?7:0) + 2*sc[0] + 1;
			ll maxInc = 2*(sc[2]+d-1) + 1;
			if (minInc < maxInc){
				sc[2] += d; break;
			} else sc[0]++, d--;
		}	
		sort(sc,sc+3);
		cout << sc[0]*sc[0] + sc[1]*sc[1] + sc[2]*sc[2] + 7*sc[0] << endl;
	}	
}
