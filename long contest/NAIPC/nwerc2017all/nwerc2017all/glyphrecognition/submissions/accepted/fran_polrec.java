import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class fran_polrec {

	static double eps = 1e-8;
	
	public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(reader.readLine());
		Point[] points = new Point[n];
		for(int i = 0; i < n; i++) {
			String[] data = reader.readLine().split(" ");
			points[i] = new Point(Integer.parseInt(data[0]), Integer.parseInt(data[1]));
		}
		solve(points);
		reader.close();
	}

	static void solve(Point[] points) {
		double bestscore = Double.NEGATIVE_INFINITY;
		int bestn = -1;
		for(int n = 3; n <= 8; n++) {
			// find outer polygon
			double lb = 0;
			double ub = 1e7;
			while(Math.abs(ub - lb) > eps) {
				double mid = (lb + ub) / 2;
				RegularPolygon P = new RegularPolygon(n, mid);
				if(P.constainsAll(points)) {
					ub = mid;
				} else {
					lb = mid;
				}
			}
			double r1 = (lb + ub) / 2;
			// find inner polygon
			lb = 0;
			ub = 1e7;
			while(Math.abs(ub - lb) > eps) {
				double mid = (lb + ub) / 2;
				RegularPolygon P = new RegularPolygon(n, mid);
				if(P.containsNone(points)) {
					lb = mid;
				} else {
					ub = mid;
				}
			}
			double r2 = (lb + ub) / 2;
			double score = r2 / r1;
			score *= score;
			if(score > bestscore) {
				bestscore = score;
				bestn = n;
			}
		}
		System.out.println(bestn + " " + bestscore);
	}
	

	
	static class Point {

		double x, y;

		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}

		public String toString() {
			return String.format("(%.3f, %.3f)", x, y);
		}

	}

	static class RegularPolygon {

		Point[] vertices;
		int n;
		double r;

		public RegularPolygon(int n, double r) {
			this.n = n;
			this.r = r;
			vertices = new Point[n];
			double alpha = 2 * Math.PI / n;
			double cur = 0;
			for(int i = 0; i < n; i++) {
				double x = r * Math.cos(cur);
				double y = r * Math.sin(cur);
				vertices[i] = new Point(x, y);
				cur += alpha;
			}
		}
		
		public double area() {
			return 0.5 * n * r * r * Math.sin(2.0 * Math.PI / n);
		}

		public boolean constainsAll(Point[] P) {
			for(Point p : P) {
				if(!contains(p)) return false;
			}
			return true;
		}
		
		public boolean containsNone(Point[] P) {
			for(Point p : P) {
				if(contains(p)) return false;
			}
			return true;
		}
		
		public boolean contains(Point p) {
			int target = orient(vertices[0], vertices[1], vertices[2]);
			for(int i = 0; i < n; i++) {
				int j = (i + 1) % n;
				int o = orient(p, vertices[i], vertices[j]);
				if(o != 0 && o != target) return false;
			}
			return true;
		}

	}

	static int orient(Point p, Point q, Point r) {
		double value = q.x * r.y - r.x * q.y - p.x * (r.y - q.y) + p.y * (r.x - q.x);
		return sgn(value);
	}
	
	public static int sgn(double x) {
		if(x < -eps) return -1;
		if(x > eps) return 1;
		return 0;
	}
	
}
