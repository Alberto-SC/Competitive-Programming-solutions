import java.util.*;
import java.io.*;


public class JimListSearch
{
	private static final boolean debug = false;
	private static final boolean timing = false;

	public static void main(String[] args) throws Exception
	{
		long start = System.currentTimeMillis();

		Scanner sc = new Scanner(System.in);
		String input = sc.next();
		int people = input.length();
		LinkedList<Integer> zeros = new LinkedList<Integer>();
		LinkedList<Integer> twos = new LinkedList<Integer>();

		int val, 
			left_zero = -1, 
			right_zero = -1, 
			idx_zero = 0;

		zeros.add(-1);
		for(int p = 0; p < people; ++p) {
			val = input.charAt(p);

			if (val == '0') {
				zeros.add(p);
			}
			if (val > '1') {
				twos.add(p);
			}
		}
		zeros.add(people);
		long after_input = System.currentTimeMillis();

        for(int i : twos) {
        	if(debug) {
	        	for(int h: zeros) {
	        		System.out.print(h + " ");
	        	}
	        	System.out.println();
	        	System.out.println("2 is at " + i);
	        }
        	while(right_zero < i) {
        		left_zero = right_zero;
        		idx_zero++;
				right_zero = zeros.get(idx_zero);
			}
			if(debug)System.out.println("left: " + left_zero + ", right: " + right_zero + ", idx_zero: " + idx_zero);

        	if (right_zero == i) {
        		zeros.remove(idx_zero);
        		right_zero = zeros.get(idx_zero);
        	} else {
				int new_zero = left_zero + right_zero - i;

				
				if (left_zero == -1 && right_zero == people) {
					// No zeros at all!
					zeros.add(idx_zero, new_zero);
					right_zero = new_zero;
				} else if (left_zero == -1) {
					// no left zero
					zeros.set(idx_zero, new_zero);
					right_zero = new_zero;
				} else if (right_zero == people) {
					// no right zero
					idx_zero--;
					zeros.set(idx_zero, new_zero);
					left_zero = zeros.get(idx_zero -1);
					right_zero = new_zero;				} else {
					// left zero is not -1 so it must not be the first or second
					zeros.remove(idx_zero);
					idx_zero--;
					zeros.set(idx_zero, new_zero);
					left_zero = zeros.get(idx_zero -1);
					right_zero = new_zero;
				}
				if(debug)System.out.println("after left: " + left_zero + ", right: " + right_zero + ", idx_zero: " + idx_zero);
			}
		}
		long after_process = System.currentTimeMillis();
		int zero_idx = zeros.poll(); // remove -1
		zero_idx = zeros.poll(); // either a number < people or people.
		for(int k = 0; k < people; ++k) {
			if (k == zero_idx) {
				zero_idx = zeros.poll();
				System.out.print('0');	
			} else {
				System.out.print('1');
			}
		}
		System.out.println();
		long finish = System.currentTimeMillis();

		if(timing) {
			System.out.println("Input " + ((after_input - start) / 1000));
			System.out.println("Processing " + ((after_process - after_input) / 1000));
			System.out.println("Output " + ((finish - after_process) / 1000));
		}
	}
}
