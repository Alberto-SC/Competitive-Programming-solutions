package com.interview.hcl;
import java.util.Arrays;

//import org.apache.commons.lang.ArrayUtils;

/**
 *
 * Java program to reverse array using Apache commons ArrayUtils class.
 * In this example we will reverse both int array and String array to
 * show how to reverse both primitive and object array in Java.
 *
 * @author
 */
public class ReverseArrayExample {

    public static void main(String args[]) {

        int[] iArray = new int[] {101,102,103,104,105};
        String[] sArray = new String[] {"one", "two", "three", "four", "five"};
       
       
        // reverse int array using Apache commons ArrayUtils.reverse() method
        System.out.println("Original int array : " + Arrays.toString(iArray));
       // ArrayUtils.reverse(iArray);
        System.out.println("reversed int array : " + Arrays.toString(iArray));
       
        // reverse String array using ArrayUtis class
        System.out.println("Original String array : " + Arrays.toString(sArray));
      //  ArrayUtils.reverse(sArray);
        System.out.println("reversed String array in Java : " + Arrays.toString(sArray));        
    }   
   
}
