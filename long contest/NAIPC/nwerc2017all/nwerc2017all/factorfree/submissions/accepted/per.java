import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.OutputStream;
import java.util.Arrays;
import java.lang.Math;

public class per {
    static int a[], parent[], prv[], nxt[];

    public static void prepare(int n, int LIM) {
        int div[] = new int[LIM+1];
        for (int i = 2; i <= LIM; ++i)
            if (div[i] == 0)
                for (int j = i; j <= LIM; j += i)
                    div[j] = i;
        int last[] = new int[LIM+1];
        Arrays.fill(last, -1);
        prv = new int[n];
        Arrays.fill(prv, -1);
        nxt = new int[n];
        Arrays.fill(nxt, n);
        for (int i = 0; i < n; ++i) {
            int v = a[i];
            while (v != 1) {
                int l = last[div[v]];
                if (l < i) {
                    prv[i] = Math.max(prv[i], l);
                    if (l != -1)
                        nxt[l] = Math.min(nxt[l], i);
                }
                last[div[v]] = i;
                v /= div[v];
            }
        }
    }
    
    public static boolean solve(int L, int R, int par) {
        if (R-L <= 0) return true;
        for (int i = L, j = R-1; i <= j; ++i, --j) {
            parent[i] = par;
            if (prv[i] < L && nxt[i] >= R)
                return solve(L, i, i) && solve(i+1, R, i);
            parent[j] = par;
            if (prv[j] < L && nxt[j] >= R)
                return solve(L, j, j) && solve(j+1, R, j);
        }
        return false;
    }
    
    public static void main(String args[]) {
        Kattio io = new Kattio(System.in, System.out);
        int n = io.getInt(), max_a = 0;
        a = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = io.getInt();
            max_a = Math.max(max_a, a[i]);
        }
        prepare(n, max_a);
        parent = new int[n];
        if (solve(0, n, -1))
            for (int i = 0; i < n; ++i)
                io.print(parent[i]+1 + " ");
        else
            io.print("impossible\n");
        io.flush();
    }
}

    
/** Simple yet moderately fast I/O routines.
 *
 * Example usage:
 *
 * Kattio io = new Kattio(System.in, System.out);
 *
 * while (io.hasMoreTokens()) {
 *    int n = io.getInt();
 *    double d = io.getDouble();
 *    double ans = d*n;
 *
 *    io.println("Answer: " + ans);
 * }
 *
 * io.close();
 *
 *
 * Some notes:
 *
 * - When done, you should always do io.close() or io.flush() on the
 *   Kattio-instance, otherwise, you may lose output.
 *
 * - The getInt(), getDouble(), and getLong() methods will throw an
 *   exception if there is no more data in the input, so it is generally
 *   a good idea to use hasMoreTokens() to check for end-of-file.
 *
 * @author: Kattis
 */


class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}
