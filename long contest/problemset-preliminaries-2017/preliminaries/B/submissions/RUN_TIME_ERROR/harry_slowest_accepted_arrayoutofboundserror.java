import java.util.Scanner;

// This is effectively a copy of mees-slow-version-of-Raymond-fast.cpp.



public class harry_slowest_accepted_arrayoutofboundserror {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Long MOD = (long) 1000000007;
		int h = sc.nextInt();
		int w = sc.nextInt();
		Long[][] dpmax = new Long[h+1][w+1];
		Long[][] dpmaxminone = new Long[h][w+1];
		
		for(int i = 0; i < h; i++)
			for(int j = 0; j <= w; j++)
			{
				dpmax[i][j] = (long)0;
				dpmaxminone[i][j] = (long)0;
			}
		
		for(int j = 0; j <= w; j++)
				dpmax[h][j] = (long)0;
		
		dpmax[1][1] = (long) 1;
		dpmaxminone[1][1] = (long) 1;
		
		for(int j = 2; j <= w; j++)
			for(int i = h; i >= 2; i--)
				for(int k = i-1; k <= h; k++)
				{
					dpmax[i][j] = (dpmax[i][j] + dpmax[k][j-1]) % MOD;
					if (i != h && k != h) dpmaxminone[i][j] = (dpmaxminone[i][j] + dpmaxminone[k][j-1]) % MOD;
				}
		
		Long answer = dpmax[h][w];
		for(int i = 1; i < h; i++)
			answer = (answer + MOD + dpmax[i][w] - dpmaxminone[i][w]) % MOD;
		
		System.out.println(answer);
		
		
	}
}
