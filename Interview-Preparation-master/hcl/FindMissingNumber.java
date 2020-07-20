package com.interview.hcl;

/*
 * Quickest way to find missing number in an array of numbers
 * @url http://stackoverflow.com/questions/2113795/quickest-way-to-find-missing-number-in-an-array-of-numbers
 */
public class FindMissingNumber {

	public static void main(String[] args) {

		int arr[] = { 1, 2, 3, 5, 6, 7, 8, 9 };

		// will be the sum of the numbers in the array.
		int sum = 0;
		int idx = -1;
		for (int i = 0; i < arr.length; i++) {
			if (arr[i] == 0) {
				idx = i;
			} else {
				sum += arr[i];
			}
		}

		// the total sum of numbers between 1 and arr.length.
		int total = (arr.length + 1) * arr.length / 2;

		System.out.println("missing number is: " + (total - sum) + " at index " + idx);
	}
}
