import java.io.*;
import java.util.*;

import static java.util.stream.Collectors.*;

public class rglclose {
  public static void main(String[] args) throws Exception {
    final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    final int n = Integer.parseInt(br.readLine());

    NavigableMap<Integer, Set<Integer>> where = new TreeMap<>();
    int[] dp = new int[n];

    int people_count = 0;
    for (String s : br.readLine().split(" ")) {
      final int h = Integer.parseInt(s);
      if (!where.containsKey(h)) where.put(h, new TreeSet<>());
      if (!where.get(h).contains(people_count-1)) where.get(h).add(people_count++);
    }

    for (Map.Entry<Integer, Set<Integer>> entry : where.descendingMap().entrySet()) {
      final Set<Integer> places = entry.getValue();

      if (where.higherEntry(entry.getKey()) == null) {
        places.forEach(x -> dp[x] = places.size() - 1);
      } else {
        final List<Integer> next = where.higherEntry(entry.getKey()).getValue().stream()
            .sorted((a, b) -> Integer.compare(
                dp[a] + (places.size() > 1 && !places.contains(a-1) ? 1 : 0),
                dp[b] + (places.size() > 1 && !places.contains(b-1) ? 1 : 0)))
            .limit(2)
            .collect(toList());
        places.forEach(j -> dp[j] = next.stream()
            .map(x -> dp[x] + (places.size() == 1
                ? (x != j+1 ? 1 : 0)
                : (x == j+1 || !places.contains(x-1) ? 1 : 0) + places.size() - 1))
            .min(Comparator.naturalOrder())
            .get());
      }
    }

    System.out.println(
        where.firstEntry().getValue().stream().map(x -> dp[x])
            .min(Comparator.naturalOrder())
            .get());
  }
}
