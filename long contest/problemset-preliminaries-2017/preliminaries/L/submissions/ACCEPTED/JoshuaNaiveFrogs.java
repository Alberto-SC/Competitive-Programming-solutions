import java.util.*;

/*
Port of joshua_naive_fast
*/

public class JoshuaNaiveFrogs {
    private Scanner s = new Scanner(System.in);

    public static void main(String[] args) {
        (new JoshuaNaiveFrogs()).solve();
    }

    private void solve() {
        long n = s.nextLong();

        Map<Long, List<Long>> classes = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            long x = s.nextLong();
            long d = s.nextLong();

            List<Long> bla = classes.get(d);
            if (bla == null) {
                bla = new ArrayList<>();
                classes.put(d, bla);
            }
            bla.add(x);
        }

        Map<Long, List<Long>> distLocs = new HashMap<>();
        long towerSize = 0;
        for (Map.Entry<Long, List<Long>> mc : classes.entrySet()) {
            Map<Long, JumpPos> modClasses = new HashMap<>();
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
                chain.add(new JumpPos(e.getKey(), pos));
                mini = Long.min(mini, recurse(chain, data, i + 1));
                chain.remove(chain.size() - 1);
            }
            return mini;
        } else {
            assert chain.size() == data.size();
            assert chain.size() > 0;
            JumpPos acc = chain.get(0);
            for (int j = 1; j < chain.size(); j++) {
                acc = merge(acc, chain.get(j));
            }
            return acc.position;
        }
    }

    private JumpPos merge(JumpPos lhs, JumpPos rhs) {
        // we don't want to modify the referenced objects here (java ...)
        lhs = new JumpPos(lhs.jumpDistance, lhs.position);
        rhs = new JumpPos(rhs.jumpDistance, rhs.position);
        while (lhs.position != rhs.position) {
            if (lhs.position > rhs.position) {
                JumpPos temp = rhs;
                rhs = lhs;
                lhs = temp;
            }

            // this check is not needed, but we avoid a division this way
            if (lhs.position + lhs.jumpDistance >= rhs.position) {
                lhs.position += lhs.jumpDistance;
                continue;
            }
            long diff = rhs.position - lhs.position;
            long m = (diff - 1) / lhs.jumpDistance + 1;
            lhs.position += m * lhs.jumpDistance;
        }

        return new JumpPos(lhs.jumpDistance * rhs.jumpDistance, lhs.position);
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
