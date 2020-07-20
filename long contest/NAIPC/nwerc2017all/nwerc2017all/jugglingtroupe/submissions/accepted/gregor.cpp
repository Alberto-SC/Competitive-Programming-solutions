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

string g;

int main(){
	cin >> g;
	vi T;
	set<int> Z; FOR(i,0,sz(g)) if (g[i] == '0') Z.insert(i); else if (g[i] == '2') T.push_back(i);
		//FORIT(z,Z) cout << *z << " ";
	   	//cout << endl;
	
	FORIT(t,T){
		Z.insert(-1); Z.insert(sz(g));
		if (Z.count(*t)) Z.erase(*t);
		else {
			int left = *(--Z.lower_bound(*t)--);
		    Z.erase(left);
			int right = *(Z.lower_bound(*t));
		    Z.erase(right);
			//cout << "E " << left << " " << right << " - " << *t << endl;
    		Z.insert(left + right - *t);
		}
		//FORIT(z,Z) cout << *z << " ";
	   	//cout << endl;
	}
	FOR(i,0,sz(g)) if (Z.count(i)) cout << "0"; else cout << "1";
	cout << endl;
}
