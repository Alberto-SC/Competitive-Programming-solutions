import java.io.*;
import java.util.*;

public class rgl {
  private static Chooser chooser;

  public static void main(String[] args) throws Exception {
    final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    final int[] tnh = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    final int t = tnh[0]; // tables
    final int n = tnh[1]; // number of group sizes
    final int h = tnh[2]; // hours open

    final int[] tables = Arrays.stream(br.readLine().split(" "))
        .mapToInt(x -> Math.min(Integer.parseInt(x), n))
        .sorted()
        .toArray();

    chooser = new Chooser(Math.max(n, h));
    System.out.format("%.9f%n", new rgl(t,n,h,tables).solveProblem(0, h).toDouble());
  }

  final int t,n,h;
  final int[] tables;

  public rgl(int t, int n, int h, int[] tables) {
    this.t = t;
    this.n = n;
    this.h = h;
    this.tables = tables;
  }

  public Answer solveProblem(int s, int peopleLeft) {
    if (s >= t) {
      return new Answer(Math.pow(n - tables[tables.length-1], peopleLeft), 0);
    }

    Answer res = solveProblem(s+1, peopleLeft);
    if (s == 0 || tables[s] > tables[s-1]) {
      for (int j = 1; j <= peopleLeft; j++) {
        res = Answer.add(
            res,
            Answer.multiply(
                getWays(s, s+j),
                solveProblem(s+j+1, peopleLeft-j),
                j,
                peopleLeft - j));
      }
    }
    return res;
  }

  Answer getWays(int l, int r) {
    int have = r - l;
    if (l == r) return Answer.ZERO;
    if (l > 0 && tables[l-1] == tables[l]) return Answer.EMPTY;

    int lo = (l == 0 ? 1 : tables[l-1] + 1);
    Answer res = Answer.EMPTY;
    for (int i = l; i < r; i++) {
      if (i+1 < r && (i+1 >= t || tables[i] == tables[i+1])) {
        continue;
      }

      int u = i-l;
      int v = r-(i+1);
      final Answer a = getWays(l, i);
      final Answer b = getWays(i+1, r);
      final Answer c;
      if (i < t) {
        int ways = (tables[i] - lo) + 1;
        c = new Answer(ways, ways * (tables[i] + lo)/2.0);
      } else {
        c = new Answer(tables[tables.length - 1] - lo + 1, 0);
      }
      res = Answer.add(
          res,
          Answer.multiply(
              c,
              Answer.multiply(a, b, u, v)));
    }
    return res;
  }

  private static class Answer {/*{{{*/
    double ways;
    double score;

    public static final Answer EMPTY = new Answer(0, 0);
    public static final Answer ZERO = new Answer(1, 0);

    public Answer(double ways, double score) {
      if (ways < 0) throw new Error("Negative number of ways");
      this.ways = ways;
      this.score = score;
    }

    public double toDouble() {
      return ways > 0 ? score / ways : 0.0;
    }

    public static Answer multiply(Answer a, Answer b) {
      return new Answer(a.ways*b.ways, a.score*b.ways+b.score*a.ways);
    }

    public static Answer multiply(Answer a, Answer b, int u, int v) {
      double c = chooser.choose(u+v, u);
      return new Answer(a.ways*b.ways*c, (a.score*b.ways+b.score*a.ways)*c);
    }

    public static Answer add(Answer a, Answer b) {
      return new Answer(a.ways+b.ways, a.score+b.score);
    }
  }/*}}}*/

  private static class Chooser {/*{{{*/
    final double[][] c;
    
    public Chooser(int n) {
      c = new double[n+1][n+1];
      for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
          c[i][j] = (i == j || j == 0 ? 1 : i < j ? 0 : c[i-1][j-1] + c[i-1][j]);
        }
      }
    }

    double choose(int a, int b) {
      return c[a][b];
    }
  }/*}}}*/
}
