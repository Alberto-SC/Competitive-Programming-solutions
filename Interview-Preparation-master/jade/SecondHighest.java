package com.interview.jade;


public class SecondHighest {

	public static void main(String[] args) {

		int size = 5;
		int[] array = AssortedMethods.randomArray(size, 0, size - 1);
		AssortedMethods.printIntArray(array);
		System.out.println(secondHighest(array));
		AssortedMethods.printIntArray(array);

	}

	
	static int secondHighest(int... nums) {
	    int high1 = Integer.MIN_VALUE;
	    int high2 = Integer.MIN_VALUE;
	    
	    for (int num : nums) {
	      if (num > high1) {
	        high2 = high1;
	        high1 = num;
	      } else if (num > high2) {
	        high2 = num;
	      }
	    }
	    return high2;
	 }
	
}
