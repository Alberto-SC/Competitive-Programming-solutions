package com.interview.forgeahead;

/*
 * url http://www.java2s.com/Code/Java/Collections-Data-Structure/Reversestheorderofthegivenchartypevaluearray.htm
 */
public class ReverseCharArray {

	
	 /**
	   * <p>Reverses the order of the given array.</p>
	   * 
	   * <p>This method does nothing for a <code>null</code> input array.</p>
	   * 
	   * @param array  the array to reverse, may be <code>null</code>
	   */
	  public static void reverse(char[] array) {
	      if (array == null) {
	          return;
	      }
	      int i = 0;
	      int j = array.length - 1;
	      char tmp;
	      while (j > i) {
	          tmp = array[j];
	          array[j] = array[i];
	          array[i] = tmp;
	          j--;
	          i++;
	      }
	  }
}
