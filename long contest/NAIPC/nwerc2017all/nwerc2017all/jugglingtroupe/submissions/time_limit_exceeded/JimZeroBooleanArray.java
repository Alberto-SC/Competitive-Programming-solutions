import java.util.*;
import java.io.*;


public class JimZeroBooleanArray
{
	public static void main(String[] args) throws Exception
	{
		long start = System.currentTimeMillis();
		Scanner sc = new Scanner(System.in);
		String input = sc.next();
		int people = input.length();
		boolean zeros[] = new boolean[people];
		LinkedList<Integer> twos = new LinkedList<Integer>();

		int val,
			left_zero,
			right_zero;

		for(int p = 0; p < people; ++p) {
			val = input.charAt(p) - 48;
			zeros[p] = val == 0 ? true : false;
			if (val > 1) {
				twos.add(p);
			}
		}

		for(int i: twos) {
			left_zero = right_zero = -1;

			if (zeros[i]) {
				zeros[i] = false;
			} else {
				for(int j = i -1; j > -1; j--) {
					if (zeros[j]) {
						left_zero = j;
						break;
					}
				}
				for(int j = i + 1; j < people; j++) {
					if (zeros[j]) {
						right_zero = j;
						break;
					}
				}
				if (left_zero > -1) {
					zeros[left_zero] = false;
				}
				if (right_zero > -1) {
					zeros[right_zero] = false;
				} else {
					right_zero = people;
				}
				zeros[left_zero + right_zero - i] = true;
			}
		}

		StringBuilder output = new StringBuilder(input.length());
		for(int k = 0; k < people; ++k) {
			output.append(zeros[k] ? '0' : '1');
		}
		System.out.println(output.toString());
	}
}
