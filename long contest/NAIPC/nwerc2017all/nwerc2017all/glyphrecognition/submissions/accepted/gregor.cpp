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



struct pt {
	double x,y;
	pt():x(0),y(0){};
	pt(double _x,double _y):x(_x),y(_y){};	
};


int main(){
	int N; cin >> N;
	vector<pt> pts(N);
	FOR(i,0,N) cin >> pts[i].x >> pts[i].y;
	
	int bestN = 0;
	double bestR = 0;
	// try all 
	FOR(n,3,9){
		// go through all points and determine "radius"
		double minR = oo, maxR = 0;
		double inang = 2.0 * PI / double(n);
		FOR(i,0,N){
			double ang = atan2(pts[i].y,pts[i].x);
			if (ang < 0) ang = 2*PI + ang;

			while (ang >= inang) ang -= inang;
			double alpha = (PI - inang)/2;
			double beta = PI - ang - alpha;
			double l = sqrt(pts[i].x*pts[i].x + pts[i].y*pts[i].y);
			double d = l * sin(beta) / sin(alpha);
			if (ang < eps) d = l;
			//cout << "D " << d << " ang: " << ang << " " << inang << endl;
			//cout << sin(ang) * l << " " << cos(ang) * l << endl;
			if (d > maxR) maxR = d;
			if (d < minR) minR = d;
		}
		double minF = n * minR * minR / 2 * sin(inang);
		double maxF = n * maxR * maxR / 2 * sin(inang);
		double r = minF / maxF;
		//cout << "R " << minR << " " <<  maxR << endl;
		//cout << "N " << n << " " << r << endl << endl;
		if (r > bestR) bestR = r, bestN = n;
	}

	cout << bestN << " " << fixed << setprecision(10) << bestR << endl;
}





























