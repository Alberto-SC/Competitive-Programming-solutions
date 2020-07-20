import java.io.*;
import java.util.*;
import java.util.stream.*;

import static java.util.stream.Collectors.*;
import static java.util.Comparator.*;

public class rglrec {
    private static long iters = 0;

    public static void main(String[] args) throws Exception {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        final int n = Integer.parseInt(br.readLine());
        List<Integer> vv = Arrays.stream(br.readLine().split(" ")).map(Integer::parseInt).collect(toList());
        final List<List<Integer>> v;
        {
          // Scope the factor array so GC deletes it quickly.
          final List<Integer>[] factors = sieve(vv.stream().max(naturalOrder()).get());
          v = vv.stream().map(x -> factors[x]).collect(toList());
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
            for (int i = l, j = r-1; i <= j; i++, j--) {
                iters++;
                if (leftBounds[i] < l && rightBounds[i] >= r) {
                    result[i] = p + 1;
                    return solve(l, i, i) && solve(i+1, r, i);
                }
                if (leftBounds[j] < l && rightBounds[j] >= r) {
                    result[j] = p + 1;
                    return solve(l, j, j) && solve(j+1, r, j);
                }
            }
            return false;
        }
    }

    private static List<Integer>[] sieve(int maxVal) {
        @SuppressWarnings("unchecked")
        final List<Integer>[] res = new List[maxVal + 1];
        final int[] factors = new int[maxVal + 1];

        res[1] = Collections.emptyList();
        for (int i = 2; i <= maxVal; i++) {
            if (factors[i] == 0) {
                res[i] = Collections.singletonList(i);
                for (int j = 1; j <= maxVal/i; j ++) {
                    factors[i*j] = i;
                }
            } else {
                if (res[i/factors[i]].contains(factors[i])) {
                    res[i] = res[i/factors[i]];
                } else {
                    res[i] = new ArrayList<>(res[i/factors[i]]);
                    res[i].add(factors[i]);
                }
            }
        }
        return res;
    }
}
