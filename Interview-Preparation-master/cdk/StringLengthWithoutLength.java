package com.interview.cdk;

public class StringLengthWithoutLength {
	
	
	public static void main(String[] args) {

	}

	public static int length(String str) {
		int count = 0;
		for (char c : str.toCharArray()) {
			count++;
		}
		return count;
	}

	
}