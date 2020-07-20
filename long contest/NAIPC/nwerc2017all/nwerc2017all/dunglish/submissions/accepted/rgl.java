import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public class rgl {
  public static void main(String[] args) {
    final Map<String, List<String>> possibleGood = new HashMap<>();
    final Map<String, List<String>> possibleAll = new HashMap<>();

    final Scanner sc = new Scanner(System.in);

    final int n = sc.nextInt();
    final List<String> words = new ArrayList<>(n);
    for (int i = 0; i < n; i++) {
      words.add(sc.next());
      possibleGood.put(words.get(i), new ArrayList<>());
      possibleAll.put(words.get(i), new ArrayList<>());
    }

    final int m = sc.nextInt();
    for (int i = 0; i < m; i++) {
      final String a = sc.next();
      final String b = sc.next();
      final String c = sc.next();
      if (possibleAll.containsKey(a)) {
        possibleAll.get(a).add(b);
        if (c.startsWith("c")) {
          possibleGood.get(a).add(b);
        }
      }
    }

    final Function<Map<String,List<String>>,Long> f = map ->
        words
            .stream()
            .map(x -> (long) map.get(x).size())
            .reduce(1L, (a,b) -> a*b);

    final long all = f.apply(possibleAll);
    final long good = f.apply(possibleGood);

    if (all == 1) {
      System.out.println(words
          .stream()
          .map(x -> possibleAll.get(x).get(0))
          .collect(Collectors.joining(" ")));
      System.out.println(all == good ? "correct" : "incorrect");
    } else {
      System.out.println("" + (good) + " correct");
      System.out.println("" + (all-good) + " incorrect");
    }
  }
}
