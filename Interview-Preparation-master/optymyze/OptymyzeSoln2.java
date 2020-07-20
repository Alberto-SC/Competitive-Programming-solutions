package com.interview.optymyze;

import java.util.Arrays;

public class OptymyzeSoln2 {
	public static void main(String[] args) {		
		char[] strArr = {'A','B','c' };			
		int len = strArr.length;
		for(int i=0;i<len/2;i++){
		    char temp=strArr[i];
		    strArr[i]=strArr[len-i-1];
		    strArr[(len)-i-1]=temp;
		}
		System.out.println(Arrays.toString(strArr));
	}
	
	
	
}

