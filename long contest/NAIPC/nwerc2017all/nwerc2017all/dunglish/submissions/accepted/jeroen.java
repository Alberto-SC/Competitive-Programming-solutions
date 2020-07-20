import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());
		String[] sent = in.readLine().split(" ");
		int m = Integer.valueOf(in.readLine());
		String[] from = new String[m];
		String[] to = new String[m];
		boolean[] corr = new boolean[m];
		for(int i = 0; i < m; i++) {
			String[] ps = in.readLine().split(" ");
			from[i] = ps[0];
			to[i] = ps[1];
			corr[i] = ps[2].equals("correct");
		}

		// Put things such that we can easily look up. Negative number is multiple,
		// positive is just 1
		Map<String, Integer> corrects = new HashMap<String, Integer>();
		Map<String, Integer> incorrects = new HashMap<String, Integer>();
		for(int i = 0; i < m; i++) {
			Map<String, Integer> dict = corr[i] ? corrects : incorrects;

			if(dict.containsKey(from[i])) {
				int old = dict.get(from[i]);
				if(old >= 0) old = -2;
				else old--;
				dict.put(from[i], old);
			} else {
				dict.put(from[i], i);
			}
		}

		// Now go through the sentence
		long num_correct = 1;
		long num_total = 1;
		List<String> single_trans = new LinkedList<String>();
		for(int i = 0; i < n; i++) {
			int count_corr = !corrects.containsKey(sent[i]) ? 0 :
				corrects.get(sent[i]) >= 0 ? 1 : -corrects.get(sent[i]);
			int count_incorr = !incorrects.containsKey(sent[i]) ? 0 :
				incorrects.get(sent[i]) >= 0 ? 1 : -incorrects.get(sent[i]);
			num_correct *= count_corr;
			num_total *= count_incorr + count_corr;
			if(num_total == 1) {
				int transi = corrects.containsKey(sent[i]) ? corrects.get(sent[i]) : incorrects.get(sent[i]);
				single_trans.add(to[transi]);
			}
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
}
