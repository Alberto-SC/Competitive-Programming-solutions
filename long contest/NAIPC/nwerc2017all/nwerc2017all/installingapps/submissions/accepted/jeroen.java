import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int c = Integer.valueOf(ps[1]);

		App[] app = new App[n];
		for(int i = 0; i < n; i++){ 
			ps = in.readLine().split(" ");
			app[i] = new App(i + 1, Integer.valueOf(ps[0]), Integer.valueOf(ps[1]));
		}

		// Sort descending by d-s, i.e. the app that requires the largest temporary
		// storage compared to its installation size should be installed first.
		Arrays.sort(app);

		// Then dp[i][j] to find out the maximum number of apps we can have
		// after the first i apps with j free space.
		int[][] dp = new int[n+1][c+1];
		App[][] ins = new App[n+1][c+1];
		for(int i = 0; i < n; i++) {
			for(int j = 0; j <= c; j++) {
				if(dp[i][j] > dp[i+1][j]) {
					dp[i+1][j] = dp[i][j];
					ins[i+1][j] = null;
				}
				if(Math.max(app[i].d, app[i].s) + j <= c && dp[i][j] >= dp[i+1][j + app[i].s]) {
					dp[i+1][j + app[i].s] = dp[i][j] + 1;
					ins[i+1][j + app[i].s] = app[i];
				}
			}
		}

		// Trace back the optimal list of apps in reverse order
		int bestc = 0;
		for(int i = 1; i <= c; i++)
			if(dp[n][i] > dp[n][bestc])
				bestc = i;
		
		List<App> ans = new ArrayList<App>();
		int curc = bestc;
		for(int i = n; i > 0; i--) {
			if(ins[i][curc] != null) {
				ans.add(ins[i][curc]);
				curc -= ins[i][curc].s;
			}
		}

		// And print them out
		Collections.reverse(ans);
		System.out.println(ans.size());
		for(App a : ans)
			System.out.print(a.idx + " ");
		System.out.println();
	}
}

class App implements Comparable<App> {
	public int idx, d, s;

	public App(int i, int d, int s) {
		this.idx = i;
		this.d = d;
		this.s = s;
	}

	public int compareTo(App other) {
		return (other.d - other.s) - (d - s);
	}
}
