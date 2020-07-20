import java.io.*;
import java.util.*;

public class SubstringSubsequence_Arknave {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s = br.readLine();
        String t = br.readLine();
        int n = s.length();
        int m = t.length();
        // let dp[j] = max i such that s[i..] has t[..j] as a substring
        int[] dp = new int[m];
        Arrays.fill(dp, -1);
        long ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = m - 1; j >= 0; --j) {
                if (s.charAt(i) == t.charAt(j)) {
                    dp[j] = j == 0 ? i : dp[j - 1];
                }
            }

            int x = dp[m - 1];
            ans += x + 1;
        }

        System.out.println(ans);
    }
}
