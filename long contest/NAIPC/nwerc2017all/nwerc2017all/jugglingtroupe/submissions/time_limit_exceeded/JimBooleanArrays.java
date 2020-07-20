import java.util.*;
import java.io.*;


public class JimBooleanArrays
{
	public static void main(String[] args) throws Exception
	{
		Scanner sc = new Scanner(System.in);
		String input = sc.next();
		int people = input.length();
		boolean zeros[] = new boolean[people];
		boolean twos[] = new boolean[people];

		int val, left_zero, right_zero;

		for(int i = 0; i < people; ++i) {
			val = input.charAt(i) - 48;
			zeros[i] = val == 0 ? true : false;
			twos[i] = val > 1 ? true : false;
		}

		for(int i = 0; i < people; ++i) {
			left_zero = right_zero = -1;
			if (twos[i]) {
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

					twos[i] = false;
					zeros[left_zero + right_zero - i] = true;
				}
			}
		}

		for(int k = 0; k < people; ++k) {
			System.out.print(zeros[k] ? '0' : '1');
		}
		System.out.println();
	}
}
