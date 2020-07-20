package com.interview.misc;

/*
 * @url https://www.tutorialspoint.com/java/java_bitwise_operators_examples.htm
 * @url https://www.tutorialspoint.com/java/java_basic_operators.htm
 * @url http://javarevisited.blogspot.in/2013/03/bitwise-and-bitshift-operators-in-java-and-or-xor-left-right-shift-example-tutorial.html
 */
public class BitwiseOperators {

   public static void main(String args[]) {
      int a = 60;	/* 60 = 0011 1100 */
      int b = 13;	/* 13 = 0000 1101 */
      int c = 0;

      c = a & b;        /* 12 = 0000 1100 */
      System.out.println("a & b = " + c );

      c = a | b;        /* 61 = 0011 1101 */
      System.out.println("a | b = " + c );

      c = a ^ b;        /* 49 = 0011 0001 */
      System.out.println("a ^ b = " + c );

      c = ~a;           /*-61 = 1100 0011 */
      System.out.println("~a = " + c );

      c = a << 2;       /* 240 = 1111 0000 */
      System.out.println("a << 2 = " + c );

      c = a >> 2;       /* 15 = 1111 */
      System.out.println("a >> 2  = " + c );

      c = a >>> 2;      /* 15 = 0000 1111 */
      System.out.println("a >>> 2 = " + c );
   }
}