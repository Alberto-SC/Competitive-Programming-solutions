package com.interview.optymyze;

import java.util.Arrays;

//Write a program to reverse an array or string
class ReverseArray {

 /* Function to reverse arr[] from start to end*/
 static void rvereseArray(int arr[], int start, int end)
 {
     int temp;
     if (start >= end)
         return;
     temp = arr[start];
     arr[start] = arr[end];
     arr[end] = temp;
     rvereseArray(arr, start+1, end-1);
 }

 /*Driver function to check for above functions*/
 public static void main (String[] args) {
     int arr[] = {1, 2, 3, 4, 5, 6};
     Arrays.toString(arr);
     rvereseArray(arr, 0, 5);
     System.out.println("Reversed array is ");
     Arrays.toString(arr);
 }
}
/*This code is contributed by Devesh Agrawal*/
