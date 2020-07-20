//Complexity: O(DN)
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(ll i = (a); i < int(b); ++i)
#define rrep(i, a, b) for(int i = (a) - 1; i >= int(b); --i)
#define trav(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

int main(){
	int N;
	cin >> N;
	map<tuple<ll,ll,ll,ll>,ll> answers;
	rep(i,0,N){
		ll A,B,C,D;
		cin >> A >> B >> C >> D;
		if(A < B)
			swap(A,B);
		if(A < C)
			swap(A,C);
		ll left=D;
		if (not answers.count(make_tuple(A,B,C,D))){
			ll &ans=answers[make_tuple(A,B,C,D)];
			rep(j,min(A,min(B,C)),1e9+2){
				if(A < j){
					++A;
					--left;
				}
				if(B < j){
					++B;
					--left;
				}
				if(C < j){
					++C;
					--left;
				}
				if(left < 0)
					break;
				ll res=7*j+(A+left)*(A+left)+B*B+C*C;
				if(res > ans)
					ans=res;
			}
			cout << ans << endl;
		} else {
			cout << answers[make_tuple(A,B,C,D)] << endl;
		}
	}
}
