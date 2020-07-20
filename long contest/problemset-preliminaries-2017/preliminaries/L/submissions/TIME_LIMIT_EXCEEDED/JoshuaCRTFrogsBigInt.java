import java.math.BigInteger;
import java.util.*;

/*
Port of joshua_met_crt_van_timon.cpp
Correct, but too slow because of bigintegers
We can probably make it faster, by combining frogs in the right order,
ensuring that numbers stay small
*/

public class JoshuaCRTFrogsBigInt {
    private Scanner s = new Scanner(System.in);

    public static void main(String[] args) {
        (new JoshuaCRTFrogsBigInt()).solve();
    }

    private void solve() {
        long n = s.nextLong();

        Map<BigInteger, List<BigInteger>> classes = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            BigInteger x = s.nextBigInteger();
            BigInteger d = s.nextBigInteger();

            List<BigInteger> bla = classes.computeIfAbsent(d, k -> new ArrayList<>());
            bla.add(x);
        }

        Map<BigInteger, List<BigInteger>> distLocs = new HashMap<>();
        BigInteger towerSize = BigInteger.ZERO;
        for (Map.Entry<BigInteger, List<BigInteger>> mc : classes.entrySet()) {
            Map<BigInteger, JumpPos> modClasses = new HashMap<>();
            BigInteger biggestClass = BigInteger.ZERO;
            for (BigInteger x : mc.getValue()) {
                BigInteger clas = x.remainder(mc.getKey());
                JumpPos jp = modClasses.get(clas);
                if (jp == null) {
                    jp = new JumpPos();
                    modClasses.put(clas, jp);
                }
                jp.jumpDistance = jp.jumpDistance.add(BigInteger.ONE); // yeah bad naming, but good reuse! Why does java not have pairs... :(
                jp.position = jp.position.max(x);

                if (jp.jumpDistance.compareTo(biggestClass) > 0) {
                    biggestClass = jp.jumpDistance;
                }
            }

            List<BigInteger> biggestIdx = new ArrayList<>();
            for (JumpPos jp : modClasses.values()) {
                if (jp.jumpDistance.equals(biggestClass)) {
                    biggestIdx.add(jp.position);
                }
            }

            assert biggestIdx.size() > 0;
            towerSize = towerSize.add(biggestClass);
            distLocs.put(mc.getKey(), biggestIdx);
        }

        assert distLocs.size() > 0;
        List<JumpPos> chain = new ArrayList<>(distLocs.size());
        List<Map.Entry<BigInteger, List<BigInteger>>> es = new ArrayList<>(distLocs.entrySet());
        assert es.size() == distLocs.size();

        BigInteger ans = recurse(chain, es, 0);

        System.out.print(ans);
        System.out.print(' ');
        System.out.println(towerSize);
    }

    private BigInteger recurse(List<JumpPos> chain, List<Map.Entry<BigInteger, List<BigInteger>>> data, int i) {
        if (i < data.size()) {
            Map.Entry<BigInteger, List<BigInteger>> e = data.get(i);
            BigInteger mini = null;
            for (BigInteger pos : e.getValue()) {
                JumpPos res = new JumpPos(e.getKey(), pos);
                if (i > 0) {
                    JumpPos prev = chain.get(i - 1);
                    res = merge(prev, res);
                }
                chain.add(res);
                if (mini == null) {
                    mini = recurse(chain, data, i + 1);
                } else {
                    mini = mini.min(recurse(chain, data, i + 1));
                }
                chain.remove(chain.size() - 1);
            }
            return mini;
        } else {
            assert chain.size() == data.size();
            assert chain.size() > 0;
            return chain.get(chain.size() - 1).position;
        }
    }

    private JumpPos merge(JumpPos lhs, JumpPos rhs) {
        JumpPos cr = crt(lhs.position.remainder(lhs.jumpDistance), lhs.jumpDistance, rhs.position.remainder(rhs.jumpDistance), rhs.jumpDistance);

        cr = align(cr, lhs.position);
        cr = align(cr, rhs.position);

        return cr;
    }

    private BigInteger mod(BigInteger a, BigInteger b) {
        return a.mod(b);
    }

    private BigInteger[] extendedEuclid(BigInteger a, BigInteger b) {
        BigInteger x = BigInteger.ONE;
        BigInteger y = BigInteger.ZERO;
        BigInteger xx = BigInteger.ZERO;
        BigInteger yy = BigInteger.ONE;

        while (b.signum() != 0) {
            BigInteger q = a.divide(b);
            BigInteger t = b;
            b = a.remainder(b);
            a = t;
            t = xx;
            xx = x.subtract(q.multiply(xx));
            x = t;
            t = yy;
            yy = y.subtract(q.multiply(yy));
            y = t;
        }
        return new BigInteger[]{x, y, a};
    }

    private JumpPos crt(BigInteger a1, BigInteger m1, BigInteger a2, BigInteger m2) {
        BigInteger[] ee = extendedEuclid(m1, m2);
        assert a1.remainder(ee[2]).equals(a2.remainder(ee[2]));
        return new JumpPos(m1.divide(ee[2]).multiply(m2), mod((ee[0].multiply(a2).remainder(m2).multiply(m1)).add(ee[1].multiply(a1).remainder(m1).multiply(m2)), m1.multiply(m2)).divide(ee[2]));
    }

    private JumpPos align(JumpPos pos, BigInteger incpos) {
        BigInteger jump = pos.jumpDistance;
        BigInteger jumps = BigInteger.ZERO.max(incpos.subtract(pos.position).add(jump).subtract(BigInteger.ONE).divide(jump));

        return new JumpPos(jump, pos.position.add(jumps.multiply(jump)));
    }

    static class JumpPos {
        BigInteger jumpDistance;
        BigInteger position;

        JumpPos(BigInteger jd, BigInteger p) {
            jumpDistance = jd;
            position = p;
        }

        JumpPos() {
            jumpDistance = BigInteger.ZERO;
            position = BigInteger.ZERO;
        }
    }
}
