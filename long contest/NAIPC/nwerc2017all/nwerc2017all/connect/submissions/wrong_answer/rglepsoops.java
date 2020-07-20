import java.awt.geom.*;
import java.io.*;
import java.util.*;

import static java.lang.Math.*;
import static java.util.stream.Collectors.*;

public class rglepsoops {
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

  private static final double EPS = 1e-9;
  private static final double BOUND = 1000000;
  private static final int N = 4;

  private static final P extrude(P o, P d) {
    double f1=(abs(d.x) < EPS? 1e30: ((d.x>0? BOUND: -BOUND)-o.x)/d.x);
    double f2=(abs(d.y) < EPS? 1e30: ((d.y>0? BOUND: -BOUND)-o.y)/d.y);
    return o.add(d.mul(min(f1, f2)));
  }

  private static final class Sector implements Comparable {
    final P centre;
    final P a;
    final P b;

    public Sector(P centre, P ab) {
      this(centre, ab, ab);
    }

    public Sector(P centre, P a, P b) {
      this.centre = centre;
      this.a = extrude(centre, a.sub(centre));
      this.b = extrude(centre, b.sub(centre));
    }

    public Sector moveTo(P re) {
      re = re.sub(centre);
      return new Sector(centre.add(re), a.add(re), b.add(re));
    }

    public Sector reversed() {
      return new Sector(centre, centre.mul(2).sub(a), centre.mul(2).sub(b));
    }

    public boolean contains(P p) {
      p = p.sub(centre);
      P u = a.sub(centre).normalised();
      P v = b.sub(centre).normalised();

      if (p.dot(u.add(v)) < -EPS) {
        return false;
      }

      double uu = p.cross(u);
      double vv = p.cross(v);
      return abs(uu) < EPS || abs(vv) < EPS || ((uu<0) != (vv<0));
    }

    public boolean isSuperset(Sector other) {
      return contains(other.centre) && contains(other.a) && contains(other.b);
    }

    @Override
    public int compareTo(Object o) {
      final Sector other = (Sector) o;
      if (!centre.like(other.centre)) return centre.compareTo(other.centre);
      if (!a.like(other.a)) return a.compareTo(other.a);
      if (!b.like(other.b)) return b.compareTo(other.b);
      return 0;
    }

    @Override
    public boolean equals(Object other) {
      return compareTo(other) == 0;
    }
  }

  private static final class Solution {
    Set<Sector> sectors = new TreeSet<Sector>();
    int cost = N*N + 1;

    final boolean contains(P p) {
      return sectors.stream().anyMatch(x -> x.contains(p));
    }

    final Solution add(Sector s, int c) {
      if (c < cost) {
        sectors.clear();
        cost = c;
      }
      if (c == cost) {
        sectors.removeAll(sectors.stream().filter(s::isSuperset).collect(toList()));
        if (sectors.stream().noneMatch(x -> x.isSuperset(s))) {
          sectors.add(s);
        }
      }
      return this;
    }
  }

  public static void main(String[] args) {
    final Scanner giveMeThe = new Scanner(System.in);

    P[] v = new P[N*N];
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        int id = giveMeThe.nextInt() - 1;
        v[id] = new P(j, N-1-i);
      }
    }

    Solution[] res = new Solution[N*N];
    for (int i = 0; i < N*N; i++) res[i] = new Solution();
    res[1].add(new Sector(v[1], v[0]).reversed(), 1);

    for (int i = 1; i+1 < N*N; i++) {
      final int cost = res[i].cost;
      for (Sector s : res[i].sectors) {
        if (args.length > 0) {
          System.err.println("  " + i + ": " + s.centre + "; " + s.a + "; " + s.b);
        }
        if (s.contains(v[i+1])) {
          res[i+1].add(new Sector(v[i+1], s.centre).reversed(), cost);
        } else {
          res[i+1].add(new Sector(v[i+1], s.centre, s.a).reversed(), cost+1);
          res[i+1].add(new Sector(v[i+1], s.centre, s.b).reversed(), cost+1);
        }
      }
    }
    System.out.println(res[N*N-1].cost);
  }
}
