import java.math.BigInteger;
import java.util.Scanner;

/*
Correct solution, but mod is only taken in the end
This means that the intermediate computations are huge
=> TLE
*/

public class BacteriaJoshuaBigIntNoMod {
    private Scanner s = new Scanner(System.in);

    public static void main(String[] args) {
        (new BacteriaJoshuaBigIntNoMod()).solve();
    }

    private void solve() {
        long n = s.nextLong();

        BigInteger MOD = BigInteger.valueOf(1000000000 + 7);
        BigInteger b = BigInteger.ONE;

        while (n > 0) {
            n--;

            BigInteger bi = s.nextBigInteger();
            b = b.shiftLeft(1).subtract(bi);

            if (b.compareTo(BigInteger.ZERO) < 0) {
                System.out.println("error");
                System.exit(0);
            }
        }

        System.out.println(b.mod(MOD));
    }
}
