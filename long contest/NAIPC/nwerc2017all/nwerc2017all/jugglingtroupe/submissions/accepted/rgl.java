import java.io.*;
import java.util.*;

public class rgl {
  public static void main(String[] args) {
    final char[] s = new Scanner(System.in).next().toCharArray();

    Stack<Integer> zerosBefore = new Stack<>(); zerosBefore.add(-1);
    Stack<Integer> zerosAfter = new Stack<>(); zerosAfter.add(s.length);

    for (int i=s.length; i-->0;) {
      if (s[i] == '0') {
        zerosAfter.push(i);
      }
    }

    for (int i=0; i<s.length; i++) {
      if (zerosAfter.peek() <= i) {
        zerosBefore.push(zerosAfter.pop());
      }
      if (s[i] >= '2') {
        int pl = zerosBefore.peek() + zerosAfter.peek() - 2*i;
        if (zerosBefore.size() > 1) s[zerosBefore.pop()]++;
        if (zerosAfter.size() > 1) s[zerosAfter.pop()]++;
        --s[i];
        --s[i+pl];
        if (s[i+pl] == '0') (pl > 0 ? zerosAfter : zerosBefore).push(i+pl);
      }
    }

    System.out.println(new String(s));
  }
}
