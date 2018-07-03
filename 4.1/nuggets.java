/*
ID: jonatha61
LANG: JAVA
TASK: nuggets
*/

import java.io.*;
import java.util.*;

public class nuggets {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("nuggets.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("nuggets.out")));

		int n = Integer.parseInt(br.readLine());
		int[] nuggets = new int[n];
		for (int i = 0; i < n; i++) {
			nuggets[i] = Integer.parseInt(br.readLine());
		}

		int gcd = nuggets[0];
		for (int i = 1; i < n; i++) {
			gcd = getGCD(gcd, nuggets[i]);
		}
		if (gcd != 1) {
			pw.println(0);
			pw.close();
			return;
		}

		boolean[] canMake = new boolean[100000];
		canMake[0] = true;

		int largestAns = 0;
		for (int i = 0; i < canMake.length; i++) {
			if (!canMake[i]) {
				largestAns = i;
			}
			else {
				for (int j = 0; j < n; j++) {
					if (i + nuggets[j] < canMake.length) {
						canMake[i + nuggets[j]] = true;
					}
				}
			}
		}

		pw.println(largestAns);
		pw.close();
	}

	static int getGCD(int a, int b) {
		while (b != 0) {
			int temp = a % b;
			a = b;
			b = temp;
		}
		return a;
	}
}