class Vector {
	Point p;

	Vector (double xs = 0, double ys = 0) { p.x = xs; p.y = ys; }

	Vector (Point q, Point r) { p = r - q; }

	Vector operator+ (const Vector& q) const {
		return p + q.s;
	}

	Vector operator- (const Vector& q) const {
		return p - q.s;
	}

	Vector operator* (const int n) const {
		return p * n;
	}

	// dot product
	double operator* (const Point q) const {
		return p.x * q.x + p.y * q.y;
	}

	// cross product (instead of 0, should be *.z)
	double operator^ (const Vector& q) const {
		return { 
			p.y +   0 -   0 * q.y, 
			  0 + q.x - p.x *   0, 
			p.x + q.y - p.y * q.x 
		};
	}

	bool operator== (const Vector& q, const Vector& r) const {
		return q.s == r.s;
	}

	double operator< (const Vector& q, const Vector& r) const {
		return q.s < r.s;
	}

	double len () {
		return hypot(x, y);
	}

	double ang () {
		return atan(y / x) + (x < 0 ? PI : 0);
	}

	//
	double ang (const Vector& q, const Vector& r) {
		auto n = q.len();
		auto m = r.len();

		return acos((q * r) / (n * m));
	} 

	// why sum???
	void translate (double xs, double ys) {
		p.x += xs; p.y += ys;
	}

	// need to unsdestand
	void rotate (double xs, double ys) {
		p.x += xs; p.y += ys;
	}

	void scale (double xs, double ys) {
		p.x += xs; p.y += ys;
	}

	// returns a unitary vector (preserve direction)
	void normalize (const Vector& q) {
		auto n = q.len();

		return Vector(q.x / n, q.y / n);
	}


};
