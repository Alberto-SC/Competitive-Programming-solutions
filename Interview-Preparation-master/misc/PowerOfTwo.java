package com.interview.misc;
/**
 * Java Program to check if a number is power of two or not.
 *
 * @url http://www.java67.com/2015/06/how-to-use-bitwise-operator-in-java.html
 */
public class PowerOfTwo{

    public static void main(String args[]) {
    	 System.out.println();
        System.out.printf("is %d power of Two? %b%n", 2, isPowerofTwo(2));
        System.out.printf("is %d power of Two? %b%n", 4, isPowerofTwo(4));
        System.out.printf("is %d power of Two? %b%n", 5, isPowerofTwo(5));
        System.out.printf("is %d power of Two? %b%n", 1, isPowerofTwo(1));
        System.out.printf("is %d power of Two? %b%n", -1, isPowerofTwo(-1));
    }

    /*
     * @return true, if number is power of two, otherwise false.
     */
    public static boolean isPowerofTwo(int number) {
        return (number & (number - 1)) == 0;
    }

}

/*
Output
is 2 power of Two? true
is 4 power of Two? true
is 5 power of Two? false
is 1 power of Two? true
is -1 power of Two? false
*/