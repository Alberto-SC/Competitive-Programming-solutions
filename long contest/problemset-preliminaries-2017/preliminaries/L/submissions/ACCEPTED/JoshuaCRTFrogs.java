import java.util.*;

/*
Port of joshua_met_crt_van_timon.cpp
*/

public class JoshuaCRTFrogs {
    private Scanner s = new Scanner(System.in);

    public static void main(String[] args) {
        (new JoshuaCRTFrogs()).solve();
    }

    private void solve() {
        long n = s.nextLong();

        Map<Long, List<Long>> classes = new TreeMap<>();
        for (int i = 0; i < n; ++i) {
            long x = s.nextLong();
            long d = s.nextLong();

            List<Long> bla = classes.computeIfAbsent(d, k -> new ArrayList<>());
            bla.add(x);
        }

        Map<Long, List<Long>> distLocs = new TreeMap<>();
        long towerSize = 0;
        for (Map.Entry<Long, List<Long>> mc : classes.entrySet()) {
            Map<Long, JumpPos> modClasses = new TreeMap<>();
            long biggestClass = 0;
            for (Long x : mc.getValue()) {
                long clas = x % mc.getKey();
                JumpPos jp = modClasses.get(clas);
                if (jp == null) {
                    jp = new JumpPos();
                    modClasses.put(clas, jp);
                }
                jp.jumpDistance++; // yeah bad naming, but good reuse! Why does java not have pairs... :(
                jp.position = Long.max(jp.position, x);

                if (jp.jumpDistance > biggestClass) {
                    biggestClass = jp.jumpDistance;
                }
            }

            List<Long> biggestIdx = new ArrayList<>();
            for (JumpPos jp : modClasses.values()) {
                if (jp.jumpDistance == biggestClass) {
                    biggestIdx.add(jp.position);
                }
            }

            assert biggestIdx.size() > 0;
            towerSize += biggestClass;
            distLocs.put(mc.getKey(), biggestIdx);
        }

        assert distLocs.size() > 0;
        List<JumpPos> chain = new ArrayList<>(distLocs.size());
        List<Map.Entry<Long, List<Long>>> es = new ArrayList<>(distLocs.entrySet());
        assert es.size() == distLocs.size();

        long ans = recurse(chain, es, 0);

        System.out.print(ans);
        System.out.print(' ');
        System.out.println(towerSize);
    }

    private long recurse(List<JumpPos> chain, List<Map.Entry<Long, List<Long>>> data, int i) {
        if (i < data.size()) {
            Map.Entry<Long, List<Long>> e = data.get(i);
            long mini = Long.MAX_VALUE;
            for (long pos : e.getValue()) {
                JumpPos res = new JumpPos(e.getKey(), pos);
                if (i > 0) {
                    JumpPos prev = chain.get(i - 1);
                    res = merge(prev, res);
                }
                chain.add(res);
                mini = Long.min(mini, recurse(chain, data, i + 1));
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
        JumpPos cr = crt(lhs.position % lhs.jumpDistance, lhs.jumpDistance, rhs.position % rhs.jumpDistance, rhs.jumpDistance);

        align(cr, lhs.position);
        align(cr, rhs.position);

        return cr;
    }

    private long mod(long a, long b) {
        return ((a % b) + b) % b;
    }

    private long[] extendedEuclid(long a, long b) {
        long x = 1;
        long y = 0;
        long xx = 0;
        long yy = 1;

        while (b != 0) {
            long q = a / b;
            long t = b;
            b = a % b;
            a = t;
            t = xx;
            xx = x - q * xx;
            x = t;
            t = yy;
            yy = y - q * yy;
            y = t;
        }
        return new long[]{x, y, a};
    }

    private JumpPos crt(long a1, long m1, long a2, long m2) {
        long[] ee = extendedEuclid(m1, m2);
        assert a1 % ee[2] == a2 % ee[2];
        return new JumpPos(m1 / ee[2] * m2, mod(((ee[0] * a2) % m2) * m1 + ((ee[1] * a1) % m1) * m2, m1 * m2) / ee[2]);
    }

    private void align(JumpPos pos, long incpos) {
        long jump = pos.jumpDistance;
        long jumps = Long.max(0, (incpos - pos.position + jump - 1) / jump);
        assert jumps <= Long.MAX_VALUE / jump;

        pos.position += jumps * jump;
    }

    static class JumpPos {
        long jumpDistance;
        long position;

        JumpPos(long jd, long p) {
            jumpDistance = jd;
            position = p;
        }

        JumpPos() {
            jumpDistance = 0;
            position = 0;
        }
    }
}
