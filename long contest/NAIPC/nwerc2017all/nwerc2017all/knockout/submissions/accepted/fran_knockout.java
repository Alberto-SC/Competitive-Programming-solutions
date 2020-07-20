import java.util.Arrays;
import java.util.Scanner;

/*
4
3 1 2 4

5
1 1 3 3 3

8
31 41 59 26 53 58 97 93


4
3 1 2 4

8
1 1 1 1 2 2 2 2

 */

public class fran_knockout {

	static int n, h;
	static int[][][] A;
	static double[] a;
	static double friend;

	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		int m = reader.nextInt();
		double[] tmp = new double[m];
		for(int i = 0; i < m; i++) {
			tmp[i] = reader.nextInt();
		}
		friend = tmp[0];
		tmp[0] = -1;
		Arrays.sort(tmp);
		tmp[0] = friend;
		h = (int)Math.ceil(Math.log(m) / Math.log(2));
		n = (1 << h);
		a = new double[n];
		int byes = n - m;
		int i = 0;
		int j = 0;
		for(i = 0; i < byes; i++) {
			a[j] = tmp[i];
			j += 2;
		}
		while(i < tmp.length) {
			a[j++] = tmp[i++];
		}	
		reader.close();
		buildA();
		double prob = solve();
		System.out.println(prob);
	}

	static double solve() {
		double[][] p = new double[h][n];
		for(int i = 0; i < n; i++) {
			int j = A[0][i][0];
			p[0][i] = a[i] / (a[i] + a[j]);
		}
		for(int k = 1; k < h; k++) {
			for(int i = 0; i < n; i++) {
				if(a[i] != 0) {
					for(int j = A[k][i][0]; j <= A[k][i][1]; j++) {
						p[k][i] += p[k - 1][j] * a[i] / (a[i] + a[j]);
					}
					p[k][i] *= p[k - 1][i];
				}
			}
		}
		return p[h - 1][0];
	}

	static void buildA() {
		A = new int[h][n][2];
		for(int i = 0; i < n; i++) {
			buildA(h - 1, i, 0, n - 1);		
		}
	}

	static void buildA(int k, int i, int L, int R) {
		if(k < 0) return;
		int M = (L + R) / 2;
		if(L <= i && i <= M) {
			// go left
			A[k][i][0] = M + 1;
			A[k][i][1] = R;
			buildA(k - 1, i, L, M);
		} else {
			// go right
			A[k][i][0] = L;
			A[k][i][1] = M;
			buildA(k - 1, i, M + 1, R);
		}
	}

}
