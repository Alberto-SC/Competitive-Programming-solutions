package com.interview.jade;

import java.util.Scanner;

class ReverseNumberWhile
{
   public static void main(String args[])
   {
      int num=0;
      int reversenum =0;
      System.out.println("Input your number and press enter: ");
      //This statement will capture the user input
      Scanner in = new Scanner(System.in);
      //Captured input would be stored in number num
      num = in.nextInt();
      
      
      //While Loop: Logic to find out the reverse number
      while( num != 0 )
      {
          reversenum = reversenum * 10;
          System.out.println("reversenum-->"+reversenum);
          
          reversenum = reversenum + num%10;
          System.out.println(num%10+"---reversenum2-->"+reversenum);
          
          num = num/10;
          System.out.println("num---------->"+num);
      }

      System.out.println("Reverse of input number is: "+reversenum);
   }
}

/*
Input your number and press enter: 
1234

reversenum-->0
reversenum2-->4
num-->123

reversenum-->40
reversenum2-->43
num-->12

reversenum-->430
reversenum2-->432
num-->1

reversenum-->4320
reversenum2-->4321
num-->0


Reverse of input number is: 4321
*/