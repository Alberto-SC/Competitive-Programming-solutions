package com.interview.optymyze;

//Reverse of any String without using any predefined function?
public class OptymyzeSoln1 {

	public static void main(String[] args) {
		String str="Hello world";
		String revstring="";
		 
		for(int i=str.length()-1;i>=0;--i){
		revstring +=str.charAt(i);
		}
		 
		System.out.println(revstring);
	}
	
	//1
	static String reverseMeIteratively(String s) {
		   StringBuilder sb = new StringBuilder();
		   for(int i = s.length() - 1; i >= 0; --i)
		     sb.append(s.charAt(i));
		   return sb.toString();
	}
	
	//2
	static String reverseMeRecursively(String s) {
		   if(s.length() == 0)
		     return "";
		   return s.charAt(s.length() - 1) + reverseMeRecursively(s.substring(0,s.length()-1));
	}
}
