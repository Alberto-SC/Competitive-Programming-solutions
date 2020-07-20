import java.util.*;

public class rgl32 {
  public static void main(String[] args) {
    final Scanner sc = new Scanner(System.in);
    for (int i = sc.nextInt(); i --> 0;) {
      final int x = (int) sc.nextLong();
      System.out.println(Integer.toString(x, 3));
    }
  }
}
