import java.util.*;
import java.io.*;

public class jeroen
{
	static int n;
	static int[] a, res;
	static Set<Integer>[] factors;
	static int[] conf_l, conf_r;
	static boolean possible;
	
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.valueOf(in.readLine());
		a = new int[n];
		String[] ps = in.readLine().split(" ");
		for(int i = 0; i < n; i++)
			a[i] = Integer.valueOf(ps[i]);

		// Compute prime factors for each element
		precomputeSieve();
		factors = new Set[n];
		for(int i = 0; i < n; i++)
			factors[i] = primeFactors(a[i]);

		// Find for each number the nearest conflict on the left ...
		conf_l = new int[n];
		Map<Integer, Integer> last = new HashMap<Integer, Integer>();
		for(int i = 0; i < n; i++) {
			conf_l[i] = -1;
			for(int f : factors[i]) {
				if(last.containsKey(f)) {
					conf_l[i] = Math.max(conf_l[i], last.get(f));
				}
				last.put(f, i);
			}
		}

		// ... and on the right
		conf_r = new int[n];
		last = new HashMap<Integer, Integer>();
		for(int i = n - 1; i >= 0; i--) {
			conf_r[i] = n;
			for(int f : factors[i]) {
				if(last.containsKey(f)) {
					conf_r[i] = Math.min(conf_r[i], last.get(f));
				}
				last.put(f, i);
			}
		}
		
		
		// Recursively fill in the whole list
		res = new int[n];
		possible = true;
		fill(0, n - 1, 0);

		// And print the output
		if(!possible)
			System.out.println("impossible");
		else {
			for(int i = 0; i < n; i++) {
				if(i > 0) System.out.print(" ");
				System.out.print(res[i]);
			}
			System.out.println();
		}
	}

	static void fill(int from, int to, int parent) {
		if(from > to) {
			return;
		} else if(from == to) {
			res[from] = parent;
		} else {
			// Search for a number that we can split on
			for(int i = 0; i < (to - from + 2) / 2; i++) {
				if(conf_l[from+i] < from && conf_r[from+i] > to) {
					res[from+i] = parent;
					fill(from,from+i-1,from+i+1);
					fill(from+i+1,to,from+i+1);
					return;
				}
				
				if(conf_l[to-i] < from && conf_r[to-i] > to) {
					res[to-i] = parent;
					fill(from,to-i-1,to-i+1);
					fill(to-i+1,to,to-i+1);
					return;
				}
			}

			// No split point found here
			possible = false;
		}
	}

	static int[] divisor;
	static final int M = 10000000;

	static void precomputeSieve() {
		divisor = new int[M+1];
		for(int i = 2; i <= M; i++)
			if(divisor[i] == 0)
				for(int j = i + i; j <= M; j += i)
					divisor[j] = i;
	}

	static Set<Integer> primeFactors(int n) {
		Set<Integer> ret = new HashSet<Integer>();

		while(divisor[n] != 0) {
			ret.add(divisor[n]);
			n /= divisor[n];
		}
		if(n > 1)
			ret.add(n);

		return ret;
	}
}
