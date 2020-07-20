package com.interview.misc;

import java.util.ArrayList;
import java.util.Arrays;

public class ListPermutations {

	public static void main(String[] args) {
		ListPermutations p = new ListPermutations();
		int[] a = {1,2,3};
		ArrayList<int[]> l = p.permutations(a);
		for(int[] i:l){
			System.out.print(Arrays.toString(i));
		}
		//[1, 2, 3][1, 3, 2][2, 1, 3][2, 3, 1][3, 2, 1][3, 1, 2]
	}

	public ArrayList<int[]> permutations(int[] a) {
		ArrayList<int[]> results = new ArrayList<>();
		permutations(a, 0, results);
		return results;
	}

	private void permutations(int[] a, int start, ArrayList<int[]> results) {
		if (start >= a.length) {
			results.add(a.clone());
		} else {
			for (int i = start; i < a.length; i++) {
				swap(a, start, i);
				permutations(a, start + 1, results);
				swap(a, start, i);
			}
		}
	}

	private void swap(int[] a, int i,int j){
		int temp = a[i];
		a[i]=a[j];
		a[j]=temp;
	}

}
