class Point {
	double x, y;

	Point (double xs = 0, double ys = 0) : x(xs), y(ys) {}

	Point operator+ (const Point& q) const {
		return { x + q.x, y + q.y };
	}

	Point operator- (const Point& q) const {
		return { x - q.x, y - q.y };
	}

	Point operator* (const int n) const {
		return { x * n, y * n };
	}

	bool operator== (const Point& q, const Point& r) const {
		return equals(q.x, r.x) and equals(q.y, r.y);
	}

	double operator< (const Point& q, const Point& r) const {
		return (fabs(q.x - r.x) < EPS) ? (r.y - q.y < EPS) : (r.x - q.x < EPS);
	}

	double dist (const Point& q, const Point& r) {
		return hypot(q.x - r.x, q.y - r.y);
	}
};
