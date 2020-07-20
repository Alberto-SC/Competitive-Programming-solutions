import java.util.Arrays;
import java.util.Scanner;

public class Joshua {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int n1 = s.nextInt();
        int[] pref1 = new int[n1];
        for(int i = 0; i < n1; ++i) {
            pref1[i] = s.nextInt();
        }

        Arrays.sort(pref1);

        int n2 = s.nextInt();
        int[] pref2 = new int[n2];
        for(int i = 0; i < n2; ++i) {
            pref2[i] = s.nextInt();
        }

        Arrays.sort(pref2);

        int answer = 0;
        int prevp = 0;

        int i = 0;
        int j = 0;
        while(i < n1 && j < n2) {
            if(pref1[i] == pref2[j]) {
                answer++;
                prevp = 0;
                i++;
                j++;
                continue;
            }
            // can p1 watch this movie?
            if(pref1[i] < pref2[j]) {
                if(prevp != 1) {
                    answer++;
                    prevp = 1;
                }
                i++;
                continue;
            }

            // can p2 watch this movie?
            if(pref2[j] < pref1[i]) {
                if(prevp != 2) {
                    answer++;
                    prevp = 2;
                }
                j++;
                continue;
            }
        }

        if(i != n1 && prevp != 1) {
            answer++;
        }

        if(j != n2 && prevp != 2) {
            answer++;
        }

        System.out.println(answer);
    }
}
