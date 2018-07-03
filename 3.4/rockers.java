/*
ID: jonatha61
LANG: JAVA
TASK: rockers
*/

/* DP */

import java.io.*;
import java.util.*;

public class rockers {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("rockers.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("rockers.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		int t = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
	
		int[] songs = new int[n + 1];
		st = new StringTokenizer(br.readLine());
		for (int i = 1; i <= n; i++) {
			songs[i] = Integer.parseInt(st.nextToken());
		}

		int maxSongs = 0;
		int[][][] dp = new int[21][21][21];

		for (int i = 0; i < m; i++) {
			for (int j = 0; j <= t; j++) {
				for (int k = 0; k <= n; k++) {
					for (int l = k + 1; l <= n; l++) {

						//new song can fit on current CD
						if (j + songs[l] <= t) {
							dp[i][j + songs[l]][l] = Math.max(dp[i][j + songs[l]][l], dp[i][j][k] + 1);
						}

						//try putting new song onto new CD
						else {
							dp[i + 1][songs[l]][l] = Math.max(dp[i + 1][songs[l]][l], dp[i][j][k] + 1);
						}
					}
					maxSongs = Math.max(maxSongs, dp[i][j][k]);
				}
			}
		}

		pw.println(maxSongs);
		pw.close();
	}
}