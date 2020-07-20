import java.util.*;

/* Based on Code by Ragnar
 * Ported by Joshua
 *
 * Does a search using a shortest path algorithm
 * Uses bitmasks to represent sets of theorems
 */

class Joshua_Ragnar_Port {
	private Scanner s = new Scanner(System.in);

	public static void main(String[] args) { (new Joshua_Ragnar_Port()).solve(); }

	private void solve() {
		// READ INPUT
		int n              = s.nextInt();
		List<Theorem> thms = new ArrayList<>(n);

		// for each theorem
		for(int i = 0; i < n; i++) {
			int p = s.nextInt();

			Theorem thm = new Theorem();
			thm.index   = i; // 0-based
			thm.proofs  = new ArrayList<>(p);

			// for each proof
			for(int j = 0; j < p; j++) {
				int l = s.nextInt();
				int k = s.nextInt();

				Proof prf  = new Proof();
				prf.length = l;

				// for each dep
				for(int m = 0; m < k; m++) {
					int d = s.nextInt() /* - 1*/; // 0-based
					prf.depMask |= (1 << d);
				}

				thm.proofs.add(prf);
			}

			thms.add(thm);
		}

		// SEARCH
		int dist[] = new int[1 << n];
		for(int i = 0; i < 1 << n; ++i) dist[i] = Integer.MAX_VALUE;
		PriorityQueue<State> work               = new PriorityQueue<>();
		work.add(new State());

		// while we're not done
		while(!work.isEmpty()) {
			State s = work.poll();

			// found it
			if((s.mask & 1) != 0) { // 0-based
				System.out.println(s.length);
				return;
			}

			// continue if the current route it too long (already visited)
			if(s.length > dist[s.mask]) { continue; }

			// look for things to prove
			for(Theorem thm : thms) {
				// already proven in context => skip
				if((s.mask & (1 << thm.index)) != 0) { continue; }

				// look for all applicable proofs of the thm
				for(Proof prf : thm.proofs) {
					// if dep <= mask (as set) (equivalently dep + mask == mask)
					// then it follows
					if((prf.depMask | s.mask) == s.mask) {
						State news  = new State();
						news.mask   = s.mask | (1 << thm.index);
						news.length = s.length + prf.length;
						if(news.length < dist[news.mask]) {
							work.add(news);
							dist[news.mask] = news.length;
						}
					}
				}
			}
		}
	}

	static class Proof {
		int depMask = 0;
		int length;
	}

	static class Theorem {
		int index;
		List<Proof> proofs;
	}

	static class State implements Comparable<State> {
		int mask   = 0;
		int length = 0;

		public int compareTo(State rhs) { return Integer.compare(length, rhs.length); }
	}
}
