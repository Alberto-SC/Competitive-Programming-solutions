import java.util.*;
import java.io.*;


public class JimListIterator
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
			right_zero = -1;

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
		ListIterator<Integer> itr = zeros.listIterator();

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
				right_zero = itr.next();
			}
			if(debug)System.out.println("left: " + left_zero + ", right: " + right_zero);

        	if (right_zero == i) {
        		itr.remove();
        		right_zero = itr.next();
        	} else {
				int new_zero = left_zero + right_zero - i;

				if (left_zero == -1 && right_zero == people) {
					if(debug)System.out.println("------ no zeros -----");
					// No zeros at all! We are on people, we need to previous, then add.
					left_zero = itr.previous(); // which will be people
					itr.add(new_zero); // add will set it BEFORE people.
					itr.previous();
					left_zero = -1; // reset everything.
				} else if (left_zero == -1) {
					if(debug)System.out.println("------ no left zero -----");
					// no left zero, set the current zero to be the new one.
					itr.set(new_zero);
				} else if (right_zero == people) {
					if(debug)System.out.println("------ right = people -----");
					// no right zero, go back two. get the new left zero.
					left_zero = itr.previous(); // back to people.
					if(debug)System.out.println("left_zero: " + left_zero);
					left_zero = itr.previous(); // people -1 this will be current left_people.
					if(debug)System.out.println("left_zero: " + left_zero);
					itr.set(new_zero); // set this to the new value.
					left_zero = itr.previous(); // got back before the current one.
					if(debug)System.out.println("left_zero: " + left_zero);
					right_zero = itr.next();
					if(debug)System.out.println("right_zero: " + right_zero);
					right_zero = itr.next();
				} else {
					if(debug)System.out.println("------ left,right -----");
					// remove the one we are on.
					itr.remove();
					if(debug)System.out.println("removing: " + right_zero);
					// left is the previous.
					left_zero = itr.previous();
					if(debug)System.out.println("left_zero: " + left_zero);
					left_zero = itr.previous();
					if(debug)System.out.println("left_zero: " + left_zero);
					right_zero = itr.next();
					if(debug)System.out.println("right_zero: " + right_zero);
					right_zero = itr.next();
					if(debug)System.out.println("right_zero: " + right_zero);
					itr.set(new_zero);

				}
				right_zero = new_zero;
				if(debug)System.out.println("after left: " + left_zero + ", right: " + right_zero);
			}
		}
		long after_process = System.currentTimeMillis();
		int zero_idx = zeros.poll(); // remove -1
		zero_idx = zeros.poll(); // either a number < people or people.
		StringBuilder output = new StringBuilder(input.length());
		for(int k = 0; k < people; ++k) {
			if (k == zero_idx) {
				zero_idx = zeros.poll();
				output.append('0');	
			} else {
				output.append('1');
			}
		}
		System.out.println(output.toString());
		long finish = System.currentTimeMillis();

		if(timing) {
			System.out.println("Input " + ((after_input - start) / 1000));
			System.out.println("Processing " + ((after_process - after_input) / 1000));
			System.out.println("Output " + ((finish - after_process) / 1000));
		}
	}
}
