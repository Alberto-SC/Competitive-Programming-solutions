import java.io.*;
import java.lang.Long;

public class Criado{
  public static long newInteger(long N, long k){
    // Two options:
    // - The MSB of N and M is different. Then, M is of the form 10...01...1.
    // - Their MSB are the same. Then, by removing the MSB, we reduce the problem to k-1 bits.

    long one= 1; // Go home, Java, you are drunk.
    long highestbit= Long.highestOneBit(N);

    if(k==1) return (N==0)?one:(highestbit*2); //base case 1: just one bit.
    if((one<<k)-1 > N) return (one<<k)-1;      //base case 2: setting last k bits to 1 suffice

    long option1= highestbit*2+(one<<k-1)-1;                // First option
    long option2= newInteger(N-highestbit, k-1)+highestbit; // Second option
    // After adding the highest bit, it may not have the required number of bits... Test if this is the case.

    return (option1<option2 || Long.bitCount(option2)!=k)?option1:option2;
  }

  public static void main(String args[]) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String line;
    line= br.readLine();
    String[] words= line.split("\\s");

    long N= Long.parseLong(words[0]);
    long k= Long.parseLong(words[1]);

    System.out.println(newInteger(N,k));
  }
}
