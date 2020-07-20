#include <bits/stdc++.h>
using namespace std;
const double tau = 4.0*acos(0.0);

struct point {
    double x, y;
    point(double x=0, double y=0): x(x), y(y) {}
    point operator-(point p) { return point(x-p.x, y-p.y); }
    double cross(point p) { return x*p.y - y*p.x; }
};

double norm(point p, int k) {
    double theta = atan2(p.y, p.x);
    if (theta < 0) theta += tau;
    int i = int(k * theta / tau);
    point q1(cos(tau*i/k), sin(tau*i/k));
    point q2(cos(tau*(i+1)/k), sin(tau*(i+1)/k));
    return p.cross(q2-q1) / q1.cross(q2-q1);
}

double score(vector<point> P, int k) {
    double r_in = 1e30, r_out = 0;
    for (auto &p: P) {
        double d = norm(p, k);
        r_in = min(r_in, d);
        r_out = max(r_out, d);
    }
    return r_in / r_out;
}

int main(void) {
    int n;
    scanf("%d", &n);
    vector<point> P(n);
    for (auto &p: P) scanf("%lf%lf", &p.x, &p.y);
    double best = 0;
    int best_k = 0;
    for (int k = 3; k <= 8; ++k) {
        double s = score(P, k);
        if (s > best) {
            best = s;
            best_k = k;
        }
    }
    printf("%d %lf\n", best_k, best*best);
}
