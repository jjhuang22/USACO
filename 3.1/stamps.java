/*
ID: jonatha61
LANG: JAVA
TASK: stamps
*/

/* standard DP */

import java.io.*;
import java.util.*;

public class stamps {
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(new FileReader("stamps.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("stamps.out")));

		int k = in.nextInt();
		int n = in.nextInt();

		int[] values = new int[n];
		for (int i = 0; i < n; i++){
			values[i] = in.nextInt();
		}

		Arrays.sort(values);
		int max = k * values[values.length - 1];
		int[] dp = new int[max + 1];
		Arrays.fill(dp, k + 1);
		dp[0] = 0;

		for (int i = 1; i <= max; i++){
			for (int j = 0; j < n; j++){
				if (i < values[j]) continue;
				dp[i] = Math.min(dp[i], dp[i - values[j]] + 1);
			}
			if (dp[i] > k){
				pw.println(i - 1);
				pw.close();
				return;
			}
		}

		pw.println(max);
		pw.close();
	}
}