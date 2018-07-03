/*
ID: jonatha61
LANG: JAVA
TASK: ratios
*/

import java.io.*;
import java.util.*;

public class ratios {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("ratios.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("ratios.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		Triple goalTrip = new Triple(Integer.parseInt(st.nextToken()), 
									 Integer.parseInt(st.nextToken()),
									 Integer.parseInt(st.nextToken()));

		int[][] mixtures = new int[3][3];
		for (int i = 0; i < 3; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < 3; j++) {
				mixtures[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		Triple currentTrip = new Triple(0, 0, 0);

		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				for (int k = 0; k < 100; k++) {
					currentTrip.setTriple(i * mixtures[0][0] + j * mixtures[1][0] + k * mixtures[2][0],
										  i * mixtures[0][1] + j * mixtures[1][1] + k * mixtures[2][1],
										  i * mixtures[0][2] + j * mixtures[1][2] + k * mixtures[2][2]);

					if (currentTrip.isMultiple(goalTrip)){
						pw.println(i + " " + j + " " + k + " " + currentTrip.x / goalTrip.x);
						pw.close();
						return;
					}			
				}
			}
		}
		pw.println("NONE");
		pw.close();
	}

	static class Triple {
		int x, y, z;

		public Triple(int x, int y, int z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public boolean isMultiple(Triple t) { 
			return (x * t.y == y * t.x && x * t.z == z * t.x && y * t.z == z * t.y && 
					!(x == 0 && y == 0 && z == 0) && 
					x >= t.x);
		}

		public void setTriple(int x, int y, int z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public String toString() {
			return (x + " " + y + " " + z);
		}
	}
}