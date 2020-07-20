import java.util.*;

public class rgl {
  public static void main(String[] args) {
    final Scanner sc = new Scanner(System.in);
    for (int i = sc.nextInt(); i --> 0;) {
      final long x = sc.nextLong();
      System.out.println(Long.toString(x, 3));
    }
  }
}
