import java.util.Scanner;

public class BacteriaJoshua {
    private long MOD = 1000000000 + 7;
    private Scanner s = new Scanner(System.in);

    public static void main(String[] args) {
        (new BacteriaJoshua()).solve();
    }

    private void solve() {
        long n = s.nextLong();

        long b = 1;
        long bm = 1;

        while (n > 0) {
            n--;

            long bi = s.nextLong();
            bm = (((bm * 2 - bi) % MOD) + MOD) % MOD;

            if (b >= 0) {
                b *= 2;
                if (b > ((long) 1 << 61))
                    b = -1;
            }
            if (b >= 0) {
                b -= bi;
                if (b < 0) {
                    System.out.println("error");
                    System.exit(0);
                }
            }
        }

        System.out.println(bm);
    }
}
