import java.io.*;
import java.util.*;

public class RglEveryoneIsUnique {
    public static void main(String[] args) {
        final Scanner scanner = new Scanner(System.in);
        final int n = scanner.nextInt();

        final int[] v = new int[n];
        final int[] s = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = scanner.nextInt();
            s[i] = v[i];
        }
        Arrays.sort(s);

        int res = 0;
        for (int i = 0; i+1 < n; i++) {
            if (bs(s, v[i]+1) != bs(s, v[i+1])) {
                res += 1;
            }
        }
        System.out.println(res);
    }

    private static final int bs(int[] v, int x) {
        int res = -1;
        for (int rad = (1<<20); rad > 0; rad >>= 1) {
            if (res + rad < v.length && v[res + rad] <= x) {
                res += rad;
            }
        }
        return res + 1;
    }
}
