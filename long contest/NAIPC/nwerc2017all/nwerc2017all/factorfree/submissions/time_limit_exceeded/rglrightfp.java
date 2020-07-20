import java.io.*;
import java.util.*;
import java.util.stream.*;

import static java.util.stream.Collectors.*;
import static java.util.Comparator.*;

public class rglrightfp {
    private static long iters = 0;

    public static void main(String[] args) throws Exception {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        final int n = Integer.parseInt(br.readLine());
        List<Integer> vv = Arrays.stream(br.readLine().split(" ")).map(Integer::parseInt).collect(toList());
        final List<Set<Integer>> v;
        {
          // Scope the factor array so GC deletes it quickly.
          final Sieve sieve = new Sieve(vv.stream().max(naturalOrder()).get());
          v = vv.stream().map(sieve::get).collect(toList());
        }

        Map<Integer, NavigableSet<Integer>> neighbours = new HashMap<>();
        for (int i = 0; i < n; i++) {
            for (int j : v.get(i)) {
                if (!neighbours.containsKey(j)) {
                    neighbours.put(j, new TreeSet<>(Arrays.asList(new Integer[] {-1, n})));
                }
                neighbours.get(j).add(i);
            }
        }
        int[] leftBounds = IntStream.range(0, n)
                .map(i -> v.get(i).stream().map(f -> neighbours.get(f).lower(i)).max(naturalOrder()).orElse(-1))
                .toArray();
        int[] rightBounds = IntStream.range(0, n)
                .map(i -> v.get(i).stream().map(f -> neighbours.get(f).higher(i)).min(naturalOrder()).orElse(n))
                .toArray();

        int[] result = new int[n];
        if (!new Solver(result, leftBounds, rightBounds).solve(0, n, -1)) {
            System.out.println("impossible");
            return;
        }
        System.err.println("" + iters + " iterations");
        System.out.println(Arrays.stream(result).mapToObj(Integer::toString).collect(joining(" ")));
    }

    private static class Solver {
        final int[] result;
        final int[] leftBounds;
        final int[] rightBounds;

        public Solver(int[] a, int[] b, int[] c) {
            result = a;
            leftBounds = b;
            rightBounds = c;
        }

        boolean solve(int l, int r, int p) {
            if (l == r) {
                return true;
            }
            for (int j = r-1; j >= l; j--) {
                iters++;
                if (leftBounds[j] < l && rightBounds[j] >= r) {
                    result[j] = p + 1;
                    return solve(l, j, j) && solve(j+1, r, j);
                }
            }
            return false;
        }
    }

    private static class Sieve {
      private final int[] factors;

      public Sieve(final int maxVal) {
        factors = new int[maxVal + 1];

        for (int i = 2; i <= maxVal; i++) {
          if (factors[i] == 0) {
            factors[i] = i;
            for (int j = i; j <= maxVal/i; j ++) {
              factors[i*j] = i;
            }
          }
        }
      }

      public Set<Integer> get(int x) {
        Set<Integer> res = new HashSet<>();
        while (x > 1) {
          res.add(factors[x]);
          x /= factors[x];
        }
        return res;
      }
    }
}
