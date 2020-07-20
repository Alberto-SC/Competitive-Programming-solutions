import java.util.*;
import java.io.*;


public class jimTwosQueue
{
	public static void main(String[] args) throws Exception
	{
		Scanner sc = new Scanner(System.in);
		String input = sc.next();
		int people = input.length();
		int gc[] = new int[people];
		Queue<Integer> twos = new LinkedList<Integer>();


		for(int i = 0; i < people; ++i) {
			gc[i] = input.charAt(i) - 48;
			if (gc[i] > 1) {
				twos.add(i);
			}
		}
		int next = 0, last;
		while(twos.peek() != null) {
			
			int two_idx = twos.remove();
			last = next; // don't add on the extra 1 until AFTER we've decided what we do.
			next = 0;
			if (gc[two_idx] > 1) {
				// If I'm not at the start, add one to the one to the left.
				if (two_idx > 0) {
					gc[two_idx-1]++;
					if (gc[two_idx-1] > 1) {
						twos.add(two_idx-1);
					}
				}

				// Need to do this here to retain ordering.
				gc[two_idx] += last;
				gc[two_idx] -= 2;
				if(gc[two_idx] > 1) {
					twos.add(two_idx);
			    }

			    // If I'm not the last element.
				if (two_idx < people -1) {
					if (gc[two_idx + 1] > 1) {
						// it will be in the two's list, and will be next. Add it on next turn.
						next = 1;
					} else {
						gc[two_idx + 1]++;
						if (gc[two_idx+1] > 1) {
							twos.add(two_idx+1);
						}	
					}
				}
					
			} else {
				gc[two_idx] += last;
				if(gc[two_idx] > 1) {
					twos.add(two_idx);
			    }	
			}

		}

		for(int k = 0; k < people; ++k) {
			System.out.print(gc[k]);
		}
		System.out.println();
	}
}
