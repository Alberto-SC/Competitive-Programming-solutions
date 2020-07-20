import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/* I took Ragnars solution as a basis.
   Because it's much shorter
 */

public class JoshuaSpinner {
    Scanner s = new Scanner(System.in);
    private int n;
    private double theta;
    private double pi = Math.PI;
    private double[][] image;
    private double[] cc = new double[4];
    private int leftmost = -1;
    private double eps = 1e-8;

    public static void main(String[] args) {
        (new JoshuaSpinner()).solve();
    }

    private void solve() {
        n = s.nextInt();
        theta = s.nextDouble();
        image = new double[n][3];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                image[i][j] = s.nextDouble();
            }
        }

        getColourCount();

        int[] fullyVisible = getFullyVisible();

        double[] m1 = rotate(getBlueMiddle(cc[fullyVisible[0]], true), fullyVisible[0] + 1);
        double[] m2 = rotate(getBlueMiddle(cc[fullyVisible[1]], false), fullyVisible[1] + 1);

        double[] ans = intersectCircles(m1, m2);

        double angle = getDirectionAngle(cc[3], ans);

        System.out.print(ans[0]);
        System.out.print(' ');
        System.out.print(ans[1]);
        System.out.print(' ');
        System.out.println(angle);
    }

    private void getColourCount() {
        boolean hasSeenColour = false;
        double anglePerPixel = theta / n;

        int colouredPixels = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                cc[j] += image[i][j] * anglePerPixel;
            }
            double sum = image[i][0] + image[i][1] + image[i][2];
            if (!hasSeenColour) {
                cc[3] += (1 - sum) * anglePerPixel;
            }

            if (sum > 0) {
                hasSeenColour = true;
                colouredPixels++;
            }
        }

        assert colouredPixels >= 2;
    }

    private int[] getFullyVisible() {
        List<Integer> order = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int sumc = 0;
            if (image[i][0] > 0) sumc++;
            if (image[i][1] > 0) sumc++;
            if (image[i][2] > 0) sumc++;
            if (sumc == 0) continue;

            int c1 = 0;
            for (; c1 < 3; c1++) {
                if (image[i][c1] > 0) break;
            }
            int c2 = c1 + 1;
            for (; c1 < 3; c1++) {
                if (image[i][c1] > 0) break;
            }

            if (sumc == 3) {
                assert order.size() > 0;
                if (c1 == back(order)) c1 = 3 - c2 - back(order);
                if (c2 == back(order)) c2 = 3 - c1 - back(order);
                sumc--;
            }

            if (sumc == 1) {
                if (order.size() == 0 || back(order) != c1) order.add(c1);
            }
            if (sumc == 2) {
                if (order.size() > 0) {
                    if (back(order) == c1) {
                        order.add(c2);
                        continue;
                    }
                    if (back(order) == c2) {
                        order.add(c1);
                        continue;
                    }
                }

                if ((c1 + 1) % 3 == c2) {
                    order.add(c1);
                    order.add(c2);
                } else {
                    order.add(c2);
                    order.add(c1);
                }
            }
        }

        leftmost = order.get(0);

        if (order.size() == 2) {
            return new int[]{order.get(0), order.get(1)};
        }

        if (cc[order.get(0)] > cc[order.get(2)])
            return new int[]{order.get(0), order.get(1)};
        else
            return new int[]{order.get(1), order.get(2)};
    }

    private double[] rotate(double[] p, int count) {
        double angle = 0;
        if (count % 3 == 1)
            angle = 2 * pi / 3;
        if (count % 3 == 2)
            angle = -2 * pi / 3;

        return new double[]{Math.cos(angle) * p[0] - Math.sin(angle) * p[1],
                Math.sin(angle) * p[0] + Math.cos(angle) * p[1]};
    }

    private double[] getBlueMiddle(double angle, boolean bottom) {
        return new double[]{-0.5, 1.0 / 2.0 / Math.tan(angle) * (bottom ? -1 : 1)};
    }

    private double[] intersectCircles(double[] m1, double[] m2) {
        double a = m1[0], b = m1[1], c = m2[0], d = m2[1];
        double divisor = (a - c) * (a - c) + (b - d) * (b - d);

        if (divisor < eps) return new double[]{2 * m1[0], 2 * m1[1]};

        double numerator = 2 * (b * c - a * d);
        return new double[]{(b - d) * numerator / divisor, -(a - c) * numerator / divisor};
    }

    private double getDirectionAngle(double blackLeader, double[] pos) {
        double[] endpoint = {-1, 0};
        endpoint = rotate(endpoint, leftmost + 1);

        double leftAngle = Math.atan2(endpoint[1] - pos[1], endpoint[0] - pos[0]);
        double beginAngle = leftAngle + blackLeader;
        double alpha = beginAngle - theta / 2;
        if (alpha > pi) alpha -= 2 * pi;
        if (alpha < -pi) alpha += 2 * pi;
        return alpha;
    }

    private Integer back(List<Integer> order) {
        return order.get(order.size() - 1);
    }
}
