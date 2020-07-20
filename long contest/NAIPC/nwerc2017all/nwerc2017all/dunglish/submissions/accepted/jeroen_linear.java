import java.util.*;
import java.io.*;

public class jeroen_linear
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());
		String[] sent = in.readLine().split(" ");
		int m = Integer.valueOf(in.readLine());
		Translation[] translations = new Translation[m];
		for(int i = 0; i < m; i++) {
			String[] ps = in.readLine().split(" ");
			translations[i] = new Translation(ps[0], ps[1], ps[2].equals("correct"));
		}


		// Now go through the sentence
		long num_correct = 1;
		long num_total = 1;
		List<String> single_trans = new LinkedList<String>();
		for(int i = 0; i < n; i++) {
			int count_corr = 0;
			int count_incorr = 0;
			String last_trans = null;
			for(Translation trans : translations) {
				if(trans.dutch.equals(sent[i])) {
					if(trans.correct) count_corr++;
					else count_incorr++;
					last_trans = trans.english;
				}
			}
			
			num_correct *= count_corr;
			num_total *= count_incorr + count_corr;
			if(num_total == 1)
				single_trans.add(last_trans);
		}

		// Print the output
		if(num_total == 1) {
			boolean first = true;
			for(String w : single_trans) {
				if(first) first = false;
				else System.out.print(" ");
				System.out.print(w);
			}
			System.out.println();
			System.out.println(num_correct == 0 ? "incorrect" : "correct");
		} else {
			System.out.println(num_correct + " correct");
			System.out.println((num_total - num_correct) + " incorrect");
		}
	}

	static class Translation {
		public String dutch, english;
		public boolean correct;
		
		public Translation(String d, String e, boolean c) {
			this.dutch = d;
			this.english = e;
			this.correct = c;
		}
	}
}
