package com.interview.mobiliya;

/*
 * Program: Write a program to convert string to number without using Integer.parseInt() method.
 * @url 1. http://www.java2novice.com/java-interview-programs/string-to-number/
 * @url 2. http://javahungry.blogspot.com/2014/02/how-to-convert-string-to-int-in-java-without-using-integer-parseint-method-code-with-example.html
 */
public class StringToInt {
	
	//1
	public static int convert_String_To_Number(String numStr){
		
		char ch[] = numStr.toCharArray();
		int sum = 0;
		//get ascii value for zero
		int zeroAscii = (int)'0';
		for(char c:ch){
			int tmpAscii = (int)c;
			sum = (sum*10)+(tmpAscii-zeroAscii);
		}
		return sum;
	}
	
	//2
	public static int stringToint( String str ){
        int i = 0, number = 0;
        boolean isNegative = false;
        int len = str.length();
        if( str.charAt(0) == '-' ){
            isNegative = true;
            i = 1;
        }
        while( i < len ){
            number *= 10;
            number += ( str.charAt(i++) - '0' );
        }
        if( isNegative )
        number = -number;
        return number;
    }   
	
	public static void main(String a[]){
		
		//1
		System.out.println("\"3256\" == "+convert_String_To_Number("3256"));
		//System.out.println("\"76289\" == "+convert_String_To_Number("76289"));
		//System.out.println("\"90087\" == "+convert_String_To_Number("90087"));
		
		//2
		 String  convertingString="123456";
	        System.out.println("String Before Conversion :  "+ convertingString);
	        int output=    stringToint( convertingString );
	        System.out.println("");
	        System.out.println("");
	        System.out.println("int value as output "+ output);
	        System.out.println("");
	        
	        String ss = "12345";
	        Integer.parseInt(ss);
		
	}
}
