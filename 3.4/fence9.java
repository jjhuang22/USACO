/*
ID: jonatha61
LANG: JAVA
TASK: fence9
*/

/* Pick's Theorem */

import java.io.*;
import java.util.*;

public class fence9 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("fence9.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("fence9.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int p = Integer.parseInt(st.nextToken());

		double a = (double) p * m / 2;
		double b = p + 1;

		if (n == 0) {
			b += m;
		}
		else {
			for (int i = 1; i <= n; i++) {
				if (isInt((double) m * i / n)) {
					b++;
				}
			}
		}

		if (n < p) {
			for (int i = 1; i < p - n; i++) {
				if (isInt((double) m - (double) m * i / (p - n))) {
					System.out.println(i);
					b++;
				}
			}
		} 
		else if (n > p) {
			for (int i = 1; i < n - p; i++) {
				if (isInt((double) m * i / (n - p))) {
					System.out.println(i);
					b++;
				}
			}
		}
		else {
			b += m - 1;
		}
		
		pw.println((int) (a - b/2 + 1));
		pw.close();
	}

	static boolean isInt(double d) { 
		return (d == (int) d);
	}
}