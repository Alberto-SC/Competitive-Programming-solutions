import java.awt.geom.*;
import java.io.*;
import java.util.*;

import static java.lang.Math.*;
import static java.util.stream.Collectors.*;

public class paul {
  private static final double EPS = 1e-11;

  private static final int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
  }

  private static final class P extends Point2D.Double implements Comparable {
    public P(double x, double y) {super(x,y);}

    double dot(P b) {return x*b.x+y*b.y;}
    double cross(P b) {return y*b.x-x*b.y;}
    P add(P b) {return new P(x+b.x,y+b.y);}
    P sub(P b) {return new P(x-b.x,y-b.y);}
    P mul(double b) {return new P(x*b,y*b);}
    P normalised() {double l = distance(0,0); return l < EPS ? this : new P(x/l, y/l);}
    boolean like(P a) {return distanceSq(a) < EPS;}

    @Override
    public int compareTo(Object b) {
      if (b instanceof P) {
        return abs(x-((P)b).x) > EPS ? java.lang.Double.compare(x, ((P)b).x) :
               abs(y-((P)b).y) > EPS ? java.lang.Double.compare(y, ((P)b).y) : 0;
      }
      throw new Error("Trying to compare P to " + b);
    }
  }

  private static final class State {
    int first = 150;
    P second;

    public State (int a,P b) {
      first = a;
      second = b;
    }
  }

  /** @return true if b lies on the ray a+s*v */
  private static boolean onRay(P a, P v, P b) {
    return abs(v.cross(b.sub(a))) < EPS && v.dot(b.sub(a)) > -EPS;
  }

  private static final double x_max = 10000;
  private static P c;

  /** @return true if the rays a+s*v and b+t*w intersect and
    * writes the intersection point in c. */
  private static boolean rays_intersect(P a, P v, P b, P w) {
    final double det = v.cross(w);
    if (abs(det) < EPS) {
      if (!onRay(a,v,b) && !onRay(b,w,a)) return false;
      if (onRay(a,v,b)) {c.x = b.x; c.y = b.y;}
      if (onRay(b,w,a)) {c.x = a.x; c.y = a.y;}
    } else {
      double s = (b.sub(a)).cross(w), t = (b.sub(a)).cross(v);
      if (s*det < -EPS || t*det < -EPS) return false;
      double ss = s/det;
      c = new P(a.x+ss*v.x,a.y+ss*v.y);
      if (abs(c.x) > x_max || abs(c.y) > x_max) return false;
    }
    return true;
  }

  private static final int K = 22;
  private static final int oo = 0x3f3f3f3f;

  static P[] ps = new P[16];
  static List<P> vs = new ArrayList<>();
  static int[][][] dist = new int[16][2*K+1][2*K+1];

  private static int getDist(State s) {
    return dist[s.first][(int)s.second.x+K][(int)s.second.y+K];
  }

  private static void setDist(State s, int val) {
    dist[s.first][(int)s.second.x+K][(int)s.second.y+K] = val;
  }

  private static void relax(Deque<State> q, State s, State t, int len) {
    if (getDist(t) > getDist(s) + len) {
      setDist(t, getDist(s) + len);
      if (len > 0) {
        q.addLast(t);
      } else {
        q.addFirst(t);
      }
    }
  };

  public static void main(String[] args) {
    final Scanner scanner = new Scanner(System.in);

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        int a = scanner.nextInt() - 1;
        ps[a] = new P(j, 3-i);
      }
    }

    for (int i = 0; i < dist.length; i++) {
      for (int j = 0; j < dist[i].length; j++) {
        for (int k = 0; k < dist[i][j].length; k++) {
          dist[i][j][k] = oo;
        }
      }
    }

    for (int x = -K; x <= +K; x++) {
      for (int y = -K; y <= +K; y++) {
        if (gcd(abs(x), abs(y)) == 1) {
          vs.add(new P(x, y));
        }
      }
    }

    Deque<State> q = new ArrayDeque<>();
    for (P v : vs) {
      dist[0][(int)v.x+K][(int)v.y+K] = 1;
      q.addLast(new State(0, v));
    }

    while (!q.isEmpty()) {
      int i = q.peekFirst().first;
      P v = q.peekFirst().second;
      q.removeFirst();

      if (i == 15) {
        continue;
      }

      // change direction at the current point i
      for (P w: vs) if (!v.like(w)) relax(q,new State(i,v),new State(i,w),1);

      // if point i+1 lies in direction v, we can go there for free
      if (onRay(ps[i],v,ps[i+1])) relax(q,new State(i,v),new State(i+1,v),0);

      // go to next point, changing direction on the way
      for (P w: vs) if (!v.like(w)) {
        if (!rays_intersect(ps[i],v,ps[i+1],new P(-w.x,-w.y))) continue;
        relax(q,new State(i,v),new State(i+1,w),1);
      }
    }

    State s = new State(15, vs.get(0));
    for (P v: vs) if (dist[15][(int)v.x+K][(int)v.y+K] < getDist(s)) s = new State(15,v);
    System.out.println("" + getDist(s));
  }
}
