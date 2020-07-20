import java.util.*;
import java.awt.geom.*;

public class PaulBinarySearch {
	
	static double polygonRadius(int k, Point2D p) {
		double rMin = 0, rMax = 5e6;
		for (int t = 0; t < 100; t++) {
			double r = (rMin + rMax) / 2;
			
			Path2D poly = new Path2D.Double();
			poly.moveTo(r,0);
			for (int i = 1; i < k; i++)
				poly.lineTo(r * Math.cos(i*2*Math.PI/k), r * Math.sin(i*2*Math.PI/k));
			poly.closePath();
			
			if (poly.contains(p)) rMax = r; else rMin = r;
		}
		return rMin;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		Point2D[] points = new Point2D[n];
		for (int i = 0; i < n; i++) {
			int x = sc.nextInt(), y = sc.nextInt();
			points[i] = new Point2D.Double(x,y);
		}
		
		int bestK = -1;
		double bestScore = 0;

		for (int k = 3; k <= 8; k++) {
			double rMin = 1e10, rMax = 0;
			for (Point2D p: points) {
				double r = polygonRadius(k, p);
				rMin = Math.min(rMin,r);
				rMax = Math.max(rMax,r);
			}
			double score = (rMin*rMin)/(rMax*rMax);
			if (score > bestScore) {
				bestK = k;
				bestScore = score;
			}
		}
		System.out.println(bestK + " " + bestScore);
	}
}
