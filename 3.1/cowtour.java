/*
ID: jonatha61
LANG: JAVA
TASK: cowtour
*/

// Floyd Warshall algorithm for all-pairs shortest path 

import java.io.*;
import java.util.*;

public class cowtour {
	static int[] x;
	static int[] y;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("cowtour.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cowtour.out")));

		int n = Integer.parseInt(br.readLine());
		x = new int[n];
		y = new int[n];

		StringTokenizer st;
		for (int i = 0; i < n; i++){
			st = new StringTokenizer(br.readLine());
			x[i] = Integer.parseInt(st.nextToken());
			y[i] = Integer.parseInt(st.nextToken());
		}

		char[][] adjacency = new char[n][n];
		double[][] distances = new double[n][n];
		for (int i = 0; i < n; i++){
			adjacency[i] = br.readLine().toCharArray();

			for (int j = 0; j < n; j++){
				if (adjacency[i][j] == '1'){
					distances[i][j] = getDistance(i, j);
				}
				else if (adjacency[i][j] == '0'){
					distances[i][j] = Double.MAX_VALUE;
				}
			}
			distances[i][i] = 0;
		}

		//floyd-warshall
		for (int k = 0; k < n; k++){
			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					distances[i][j] = Math.min(distances[i][j], distances[i][k] + distances[k][j]);
				}
			}
		}

		//calculate largest diamater in connected vertices 
		double[] maxdiameter = new double[n];
		double maxd = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (distances[i][j] != Double.MAX_VALUE){
					maxdiameter[i] = Math.max(maxdiameter[i], distances[i][j]);
					maxd = Math.max(maxd, maxdiameter[i]);
				}
			}
		}

		//add in an extra path
		double maxd2 = Double.MAX_VALUE;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (distances[i][j] == Double.MAX_VALUE){
					maxd2 = Math.min(maxd2, maxdiameter[i] + maxdiameter[j] + getDistance(i, j));
				}
			}
		}

		pw.println(String.format("%.6f", Math.max(maxd, maxd2)));
		pw.close();
	}

	static double getDistance(int i, int j){
		return Math.sqrt(Math.pow(x[i] - x[j], 2) + Math.pow(y[i] - y[j], 2));
	}
}