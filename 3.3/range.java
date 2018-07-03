/*
ID: jonatha61
LANG: JAVA
TASK: range
*/

import java.io.*;
import java.util.*;

public class range {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("range.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("range.out")));

		int n = Integer.parseInt(br.readLine());
		int[][] field = new int[n][n];
		for (int i = 0; i < n; i++) {
			String newLine = br.readLine();
			
			for (int j = 0; j < n; j++) {
				field[i][j] = Integer.parseInt(newLine.substring(j, j+1));
			}
		}


		int[][] dp = new int[n][n];
		dp[0] = field[0];
		for (int i = 1; i < n; i++) {
			dp[i][0] = field[i][0];
		}

		int[] squareCount = new int[n + 1];

		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				if (field[i][j] == 0) continue;
				dp[i][j] = 1 + Math.min(dp[i-1][j-1], Math.min(dp[i][j-1], dp[i-1][j]));
			
				//keep track of counts of each square size
				squareCount[dp[i][j]]++;
			}
		}

		//test dp 
		// for (int i = 0; i < n; i++) {
		// 	for (int j = 0; j < n; j++) {
		// 		System.out.print(dp[i][j]);
		// 	}
		// 	System.out.println();
		// }

		for (int i = n - 1; i >= 2; i--) {
			squareCount[i] += squareCount[i + 1];
		}
		
		for (int i = 2; i <= n; i++) {
			if (squareCount[i] != 0) {
				pw.println(i + " " + squareCount[i]);
			}
		}
		pw.close();
	}
}