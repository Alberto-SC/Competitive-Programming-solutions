// O(N)
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
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
	rep(i,0,N){
		ll A,B,C,D;
		cin >> A >> B >> C >> D;
		if(A < B)
			swap(A,B);
		if(A < C)
			swap(A,C);
		if(B < C)
			swap(B,C);
		ll ans=(A+D)*(A+D)+B*B+C*C+7*C;
		ll a=A,b=B,c=C,d=D;
		ll addC=min(b-c, d);
		c += addC;
		d -= addC;
		ans=max(ans, (a+d)*(a+d)+b*b+c*c+7*c);
		ll addB=min(a-b, d/2);
		b += addB;
		c += addB;
		d -= 2*addB;
		ans=max(ans, (a+d)*(a+d)+b*b+c*c+7*c);
		ll addA=d/3;
		a += addA;
		b += addA;
		c += addA;
		d -= 3*addA;
		ans=max(ans, (a+d)*(a+d)+b*b+c*c+7*c);
		cout << ans << endl;
	}
}
