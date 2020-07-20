#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define ST(s) s.first][s.second.x+K][s.second.y+K

template<typename num>
struct point {
	num x, y;
	point operator+(const point &p) const { return {x+p.x,y+p.y}; }
	point operator-(const point &p) const { return {x-p.x,y-p.y}; }
	point operator-() const { return {-x,-y}; }
	num operator*(const point &p) const { return x*p.x + y*p.y; }
	num operator%(const point &p) const { return x*p.y - y*p.x; }
	bool operator!=(const point &p) const { return x != p.x || y != p.y; }
};

typedef pair<int,point<int>> state;

// returns true if b lies on the ray a+s*v
bool on_ray(point<int> a, point<int> v, point<int> b) {
	return v % (b-a) == 0 && v * (b-a) >= 0;
}

const double x_max = 100;

point<double> c;
// returns true if the rays a+s*v and b+t*w intersect and writes the intersection point in c
bool rays_intersect(point<int> a, point<int> v, point<int> b, point<int> w) {
	int det = v % w;
	if (det == 0) {
		if (!on_ray(a,v,b) && !on_ray(b,w,a)) return false;
		if (on_ray(a,v,b)) c.x = b.x, c.y = b.y;
		if (on_ray(b,w,a)) c.x = a.x, c.y = a.y;
	} else {
		int s = (b-a) % w, t = (b-a) % v;
		if (s*det < 0 || t*det < 0) return false;
		double ss = double(s)/det;
		c = {a.x+ss*v.x,a.y+ss*v.y};
		if (abs(c.x) > x_max || abs(c.y) > x_max) return false;
	}
	return true;
}

const int K = 100, oo = 0x3f3f3f3f;

vector<point<int>> ps(16), vs;
int dist[16][2*K+1][2*K+1];
state pred[16][2*K+1][2*K+1];

int main(int argc,char **argv) {
	FOR(i,0,3) FOR(j,0,3) {
		int a; cin >> a;
		ps[a-1].x = j, ps[a-1].y = 3-i;
	}
	
	FOR(x,-K,K) FOR(y,-K,K) if (abs(__gcd(x,y)) == 1) vs.push_back({x,y});

	memset(dist,0x3f,sizeof dist);
	
	deque<state> q;
	for (auto v: vs) {
		dist[0][v.x+K][v.y+K] = 1;
		q.emplace_back(0,v);
	}
	
	auto relax = [&](state s, state t, int len) {
		if (dist[ST(t)] > dist[ST(s)] + len) {
			dist[ST(t)] = dist[ST(s)] + len;
			pred[ST(t)] = len ? s : pred[ST(s)];
			if (len) q.push_back(t);
			else q.push_front(t);
		}
	};
	
	while (!q.empty()) {
		int i; point<int> v;
		tie(i,v) = q.front();
		q.pop_front();

		if (i == 15) continue;

		// change direction at the current point i
		for (auto w: vs) if (v != w) relax({i,v},{i,w},1);

		// if point i+1 lies in direction v, we can go there for free
		if (on_ray(ps[i],v,ps[i+1])) relax({i,v},{i+1,v},0);

		// go to next point, changing direction on the way
		for (auto w: vs) if (v != w) {
			if (!rays_intersect(ps[i],v,ps[i+1],-w)) continue;
			relax({i,v},{i+1,w},1);
		}
	}
	
	state s(15,vs[0]);
	for (auto v: vs) if (dist[15][v.x+K][v.y+K] < dist[ST(s)]) s = {15,v};
	cout << dist[ST(s)] << endl;

	vector<point<double>> path;
	for (;dist[ST(s)] > 1; s = pred[ST(s)]) {
		int i,j; point<int> v,w;
		tie(i,v) = pred[ST(s)], tie(j,w) = s;
		rays_intersect(ps[i],v,ps[j],-w);
		path.push_back(c);
	}
	
	if (argc > 1) {
		reverse(begin(path),end(path));
		cout << fixed << setprecision(10);
		cout << ps[0].x << " " << ps[0].y << endl;
		for (auto p: path) cout << p.x << " " << p.y << endl;
		cout << ps[15].x << " " << ps[15].y << endl;
	}
}
