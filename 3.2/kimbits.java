/*
ID: jonatha61
LANG: JAVA
TASK: kimbits
*/

import java.io.*;
import java.util.*;

public class kimbits {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("kimbits.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("kimbits.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		int l = Integer.parseInt(st.nextToken());
		Long I = Long.parseLong(st.nextToken());

		int[][] dp = new int[l + 1][n + 1];
		Arrays.fill(dp[0], 1);
		for (int i = 0; i <= l; i++) {
			dp[i][0] = 1;
		}

		//fill in dp array 
		for (int i = 1; i <= l; i++) {
			for (int j = 1; j <= n; j++) {
				dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
			}
		}

		String answer = "";
		int level = l;
		while (answer.length() < n) {
			if (I > dp[level][n - answer.length() - 1]) {
				I -= dp[level][n - answer.length() - 1];
				answer += "1";
				level--;
			}
			else {
				answer += "0";
			}
		}

		pw.println(answer);
		pw.close();
	}
}