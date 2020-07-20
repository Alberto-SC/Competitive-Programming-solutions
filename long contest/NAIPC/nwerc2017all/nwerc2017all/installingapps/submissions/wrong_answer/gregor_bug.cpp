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

int d[1000];
int s[1000];

pair<int,pii> x[1000];

#define A (20000*600)
#define B (600)

int dp[20000];
int pa[20000];

int main(){
		int n,c; cin >> n >> c;
		FOR(i,0,n) cin >> d[i] >> s[i], x[i].first = s[i]-d[i],
	   									x[i].second.first = d[i],
									    x[i].second.second = i;

		sort(x,x+n);

		FOR(i,0,c+1) dp[i] = 0, pa[i] = -1;

		int maxi = 0;
		FOR(i,0,n) {
				int D = x[i].second.first;
				int S = x[i].first + D;
				int k = x[i].second.second;
				FORD(j,1,c+1){
						if (j+max(0,D-S) > c || j-S < 0) continue;
						if (dp[j-S]+1 > dp[j]) dp[j] = dp[j-S]+1, pa[j] = i;
						maxi = max(maxi,dp[j]);
				}
		}
		int t = 0;
		while (dp[t] != maxi) t++;
		vi s;
		while (t != 0){
				s.push_back(x[pa[t]].second.second);
				int r = x[pa[t]].first + x[pa[t]].second.first;
				t -= r;
		}

		cout << maxi << endl;
		reverse(all(s));
		FOR(i,0,sz(s)) cout << (i?" ":"") << s[i]+1;
		cout << endl;

}
