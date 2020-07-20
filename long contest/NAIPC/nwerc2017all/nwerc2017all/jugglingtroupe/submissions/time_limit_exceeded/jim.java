import java.util.*;
import java.io.*;

public class jim
{
	public static void main(String[] args) throws Exception
	{
		Scanner sc = new Scanner(System.in);
		String input = sc.next();
		int people = input.length();
		int gc[] = new int[people];
		boolean again = false;

		for(int i = 0; i < people; ++i) {
			gc[i] = input.charAt(i) - 48;
			if (gc[i] > 1) {
				again = true;
			}
		}

		while(again) {
			int next = 0, last;
			again = false;
			for(int j = 0; j < people; ++j) {
				last = next; // don't add on the extra 1 until AFTER we've decided what we do.
				next = 0;
				if (gc[j] > 1) {
					if (j > 0) {
						gc[j-1]++;
					}
					next = 1; // if the last one this is 'thrown away'
					again = true;
					gc[j] -= 2;		
				}
				gc[j] += last;
			}
			// for(int k = 0; k < people; ++k) {
			// 	System.out.print(gc[k]);
			// }
			// System.out.println();
		}

		for(int k = 0; k < people; ++k) {
			System.out.print(gc[k]);
		}
		System.out.println();
	}
}
