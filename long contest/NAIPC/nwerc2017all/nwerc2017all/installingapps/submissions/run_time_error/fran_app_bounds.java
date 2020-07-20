import java.util.Arrays;
import java.util.Scanner;

public class fran_app_bounds {

	static int n, c;
	static App[] app;

	static int INSTALL = 0, SKIP = 1;
	static Integer[][] memo;
	static Integer[][] parent;


	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		n = reader.nextInt();
		c = reader.nextInt();
		app = new App[n];
		for(int i = 0; i < n; i++) {
			app[i] = new App(reader.nextInt(), reader.nextInt(), i + 1);
		}
		Arrays.sort(app);
		memo = new Integer[n][c + 1];
		parent = new Integer[c][c + 1];
		solve(0, c);
		printSol();
		reader.close();
	}

	static int solve(int i, int cap) {
		if(i == n) {
			return 0;
		}
		if(memo[i][cap] != null) {
			return memo[i][cap];
		}
		int install = Integer.MIN_VALUE;
		if(Math.max(app[i].d, app[i].s) <= cap) {
			install = 1 + solve(i + 1, cap - app[i].s);
		}
		int skip = solve(i + 1, cap);
		if(install > skip) {
			memo[i][cap] = install;
			parent[i][cap] = INSTALL;
		} else {
			memo[i][cap] = skip;
			parent[i][cap] = SKIP;
		}
		return memo[i][cap];
	}

	static void printSol() {
		int value = memo[0][c];
		System.out.println(value);
		int cap = c;
		for(int i = 0; i < n; i++) {
			if(parent[i][cap] == INSTALL) {
				System.out.print(app[i].index);
				cap -= app[i].s;
				value -= 1;
				if(value > 0) {
					System.out.print(" ");	
				}
			}
		}
		System.out.println();
	}

	static class App implements Comparable<App> {

		int d, s, index;

		public App(int d, int s, int index) {
			this.d = d;
			this.s = s;
			this.index = index;
		}

		public String toString() {
			return String.format("(%d, %d)", d, s);
		}

		public int compareTo(App o) {
			int v1 = s - d;
			int v2 = o.s - o.d;
			return v1 - v2;
		}

	}

}
