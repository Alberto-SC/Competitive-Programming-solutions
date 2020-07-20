package com.interview.ptc;

public class SwapVariables {
	public static void main(String[] args) {
		int x=10;
		int y=5;
		
		x=0b1010;
		y=0b0101;
		
		System.out.println("x="+x+" ,  y="+y);
		swap1(x,y);
		swap2(x,y);
	}

	public static void swap1(int x, int y) {
		x = x + y;
		y = x - y;
		x = x - y;
		System.out.println("x="+x+" ,  y="+y);
	}

	/*@url http://www.programmerinterview.com/index.php/java-questions/xor-in-java/
	 * The XOR operator will return a 1, or TRUE, if both numbers being compared are different. But, 
	 * if the numbers being compared are the same it will return a 0 for FALSE.
	 * @url https://en.wikipedia.org/wiki/Exclusive_or
	 * This could be written as "A or B, but not, A and B".
	 */
	public static void swap2(int x, int y) {
		x = x ^ y;
		y = x ^ y;
		x = x ^ y;
		System.out.println("x="+x+" ,  y="+y);
	}
}
