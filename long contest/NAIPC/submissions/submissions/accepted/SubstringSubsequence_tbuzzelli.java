import java.util.*;
import java.io.*;

public class SubstringSubsequence_tbuzzelli {
    static int oo = 1000000000;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        char[] str = br.readLine().toCharArray();
        char[] tStr = br.readLine().toCharArray();
        int n = str.length;
        int m = tStr.length;
        int[][] nexts = new int[n + 1][26];
        Arrays.fill(nexts[n], oo);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++)
                nexts[i][j] = nexts[i + 1][j];
            nexts[i][str[i] - 'a'] = i;
        }
        long ans = 0;
        for (int i = 0; i < n; i++) {
            int idx = i, j;
            for (j = 0; j < m && idx < n; idx = nexts[idx][tStr[j++] - 'a'] + 1);
            if (idx < oo && j == m) ans += n - idx + 1;
        }
        System.out.println(ans);
    }
}
