import java.util.LinkedList;
import java.util.Scanner;
import java.util.TreeSet;

public class Francois {

	public static void main(String[] args) {
		// read input
		Scanner reader = new Scanner(System.in);
		String s = reader.nextLine();
		reader.close();
		// build zeros and two data structures
		TreeSet<Integer> zeros = new TreeSet<>();
		LinkedList<Integer> twos = new LinkedList<>();
		for(int i = 0; i < s.length(); i++) {
			if(s.charAt(i) == '0') zeros.add(i);
			else if(s.charAt(i) == '2') twos.add(i);
		}
		// simulate
		for(int t : twos) {
			zeros.add(-1);
			zeros.add(s.length());
			if(zeros.contains(t)) {
				zeros.remove(t);
			} else {
				int left = zeros.lower(t);
				int right = zeros.higher(t);
				zeros.remove(left);
				zeros.remove(right);
				zeros.add(left + right - t);
			}
		}
		// output
		for(int i = 0; i < s.length(); i++) {
			System.out.print(zeros.contains(i) ? "0" : "1");
		}
		System.out.println();
	}
	
}
