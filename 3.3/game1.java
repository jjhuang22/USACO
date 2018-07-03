/*
ID: jonatha61
LANG: JAVA
TASK: game1
*/

import java.io.*;
import java.util.*;

public class game1 {
	static int[][] dp;
	static int[] board;
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(new FileReader("game1.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("game1.out")));

		int n = in.nextInt();
		board = new int[n + 1];
		int totalSum = 0;
		for (int i = 1; i <= n; i++) {
			board[i] = in.nextInt();
			totalSum += board[i];
		}	

		dp = new int[101][101];
		int aScore = recurse(1, n);
		pw.println(aScore + " " + (totalSum - aScore));
		pw.close();
	}

	static int recurse(int m, int n) {
		if (m == n){
			dp[m][m] = board[m];
			return dp[m][m];
		}
		if (m > n) return 0;
		if (dp[m][n] != 0) return dp[m][n];

		dp[m][n] = Math.max( 
					board[m] + Math.min(recurse(m+2, n), recurse(m+1, n-1)),
					board[n] + Math.min(recurse(m+1, n-1), recurse(m, n-2)));
		
		return dp[m][n];
	}
}