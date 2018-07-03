/*
ID: jonatha61
LANG: JAVA
TASK: spin
*/

import java.io.*;
import java.util.*;

public class spin {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("spin.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("spin.out")));

		int[] speed = new int[5];
		int[] wedges = new int[5];
		int[][] wedgeStart = new int[5][5];
		int[][] wedgeExt = new int[5][5];

		for (int i = 0; i < 5; i++){
			Arrays.fill(wedgeStart[i], -1);
			Arrays.fill(wedgeExt[i], -1);
		}

		StringTokenizer st;
		for (int i = 0; i < 5; i++) {
			st = new StringTokenizer(br.readLine());
			speed[i] = Integer.parseInt(st.nextToken());
			wedges[i] = Integer.parseInt(st.nextToken());

			for (int j = 0; j < wedges[i]; j++) {
				wedgeStart[i][j] = Integer.parseInt(st.nextToken());
				wedgeExt[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		for (int t = 0; t <= 360; t++) {
			int[] valid = new int[361];

			for (int i = 0; i < 5; i++) {
				int loc = (t * speed[i]) % 360; 

				for (int j = 0; j < wedges[i]; j++) {
					for (int k = wedgeStart[i][j]; k <= wedgeStart[i][j] + wedgeExt[i][j]; k++) {
						int endLoc = (k + loc) % 360;
						valid[endLoc]++;
						if (valid[endLoc] == 5) {
							pw.println(t);
							pw.close();
							return;
						}
					}
				}
			}
		}

		pw.println("none");
		pw.close();
	}
}