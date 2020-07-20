import java.io.*;
import java.util.*;
import java.util.stream.*;

public class rgl {
  public static void main(String[] args) throws Exception {
    final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    // Read gears.
    final int n = Integer.parseInt(br.readLine());
    final List<Integer> gears = new ArrayList<>();
    final List<Map<Integer, Integer>> edges = new ArrayList<>();
    final List<Set<Eqn>> eqns = new ArrayList<>();
    for (String s : br.readLine().split(" ")) {
      gears.add(Integer.parseInt(s));
      edges.add(new HashMap<>());
      eqns.add(new TreeSet<>());
    }

    // Read edges.
    final int m = Integer.parseInt(br.readLine());
    for (int i = 0; i < m; i++) {
      String[] s = br.readLine().split(" ");
      final int a = Integer.parseInt(s[0]) - 1;
      final int b = Integer.parseInt(s[1]) - 1;
      final int w = Integer.parseInt(s[2]);
      edges.get(a).put(b, w);
      edges.get(b).put(a, w);
    }

    // Find all the equations. Mark out the ones with maximum c.
    eqns.get(0).add(new Eqn(1, 0));
    dfs(0, edges, new HashSet<>(), eqns);
    Set<Eqn> best = new TreeSet<>();
    eqns.stream().flatMap(x -> x.stream())
        .filter(f -> f.m >= 1)
        .max(Comparator.naturalOrder())
        .ifPresent(f -> best.add(f));
    eqns.stream().flatMap(x -> x.stream())
        .filter(f -> f.m <= 0)
        .max(Comparator.naturalOrder())
        .ifPresent(f -> best.add(f));

    // We know the value of the max gear. Find the equation that corresponds to it.
    final int maxGear = gears.stream().max(Comparator.naturalOrder()).get();

    for (Eqn eq : best) {
      final int gear0 = eq.inverse(maxGear);
      final Map<Integer, Queue<Integer>> available = indexMap(gears);

      Optional<List<Integer>> res = validateSolution(gear0, available, eqns);
      if (res.isPresent()) {
        System.out.println(
            res.get().stream().map(Object::toString).collect(Collectors.joining(" ")).toString());
        return;
      }
    }
    System.out.println("impossible");
  }

  private static Optional<List<Integer>> validateSolution(
      int gear0,
      Map<Integer, Queue<Integer>> available,
      List<Set<Eqn>> eqns) {
    List<Integer> result = new ArrayList<>();
    for (int i = 0; i < eqns.size(); i++) {
      // Find the value for this axle.
      int v = eqns.get(i).iterator().next().eval(gear0);

      // Assign one of the available gears of this size to the axle.
      if (!available.containsKey(v) || available.get(v).isEmpty()) {
        return Optional.empty();
      }
      result.add(available.get(v).remove());

      // Make sure all of the equations give the same result.
      for (Eqn e : eqns.get(i)) {
        if (e.eval(gear0) != v) {
          return Optional.empty();
        }
      }
    }
    return Optional.of(result);
  }

  private static void dfs(
      int x,
      List<Map<Integer, Integer>> edges,
      Set<Integer> done,
      List<Set<Eqn>> fun) {
    done.add(x);

    for (int y : edges.get(x).keySet()) {
      for (Eqn f : fun.get(x)) {
        fun.get(y).add(new Eqn(-f.m, edges.get(x).get(y)-f.c));
      }
      if (!done.contains(y)) {
        dfs(y, edges, done, fun);
      }
    }
  }

  private static Map<Integer, Queue<Integer>> indexMap(List<Integer> arr) {
    Map<Integer, Queue<Integer>> map = new HashMap<>();
    for (int i = 0; i < arr.size(); i++) {
      if (!map.containsKey(arr.get(i))) {
        map.put(arr.get(i), new ArrayDeque<>());
      }
      map.get(arr.get(i)).add(i+1);
    }
    return map;
  }

  private static class Eqn implements Comparable<Eqn> {
    final int m;
    final int c;

    public Eqn(int m, int c) {
      this.m = m;
      this.c = c;
    }

    public int eval(int x) {
      return m*x + c;
    }

    public int inverse(int y) {
      return (y - c) / m;
    }

    @Override
    public boolean equals(Object other) {
      return other instanceof Eqn && m == ((Eqn) other).m && c == ((Eqn) other).c;
    }

    @Override
    public int compareTo(Eqn other) {
      return c != other.c ? Integer.compare(c, other.c) : Integer.compare(m, other.m);
    }
  }
}
