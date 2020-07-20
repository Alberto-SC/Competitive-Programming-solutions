import java.math.BigInteger;
import java.util.Scanner;

public class BacteriaJoshuaBigInt {
    private Scanner s = new Scanner(System.in);

    public static void main(String[] args) {
        (new BacteriaJoshuaBigInt()).solve();
    }

    private void solve() {
        long n = s.nextLong();

        BigInteger MOD = BigInteger.valueOf(1000000000 + 7);
        BigInteger BND = BigInteger.valueOf((long) 1 << 61);
        BigInteger b = BigInteger.ONE;
        BigInteger bm = BigInteger.ONE;

        while (n > 0) {
            n--;

            BigInteger bi = s.nextBigInteger();
            bm = bm.shiftLeft(1).subtract(bi).mod(MOD); // mod gives non negative results

            if (b.signum() >= 0) {
                b = b.shiftLeft(1);
                if (b.compareTo(BND) > 0)
                    b = BigInteger.ONE.negate();
            }
            if (b.signum() >= 0) {
                b = b.subtract(bi);
                if (b.signum() < 0) {
                    System.out.println("error");
                    System.exit(0);
                }
            }
        }

        System.out.println(bm);
    }
}
