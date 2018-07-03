/*
ID: jonatha61
LANG: JAVA
TASK: inflate
*/

/* standard DP */

import java.io.*;
import java.util.*;

public class inflate {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("inflate.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("inflate.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		int m = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken()); 

		int[] points = new int[n];
		int[] minutes = new int[n];

		for (int i = 0; i < n; i++){
			st = new StringTokenizer(br.readLine());
			points[i] = Integer.parseInt(st.nextToken());
			minutes[i] = Integer.parseInt(st.nextToken());
		}

		int[] dp = new int[m+1];
		for (int i = 1; i <= m; i++){
			for (int j = 0; j < n; j++){
				if (minutes[j] <= i){
					dp[i] = Math.max(dp[i], dp[i - minutes[j]] + points[j]);
				}
			}
		}
		pw.println(dp[m]);
		pw.close();
	}
}