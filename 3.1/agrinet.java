/*
ID: jonatha61
LANG: JAVA
TASK: agrinet
*/

/* Prim's algorithm using PriorityQueue with custom Comparator */


import java.io.*;
import java.util.*;

public class agrinet {
	public static void main(String[] args) throws IOException {
		//BufferedReader br = new BufferedReader(new FileReader("agrinet.in"));
		Scanner in = new Scanner(new File("agrinet.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("agrinet.out")));

		int n = in.nextInt();
		int[][] connectivity = new int[n][n];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				connectivity[i][j] = in.nextInt();
			}
		}

		int minDist = 0;
		
		int[] distances = new int[n];
		Arrays.fill(distances, Integer.MAX_VALUE);
		distances[0] = 0;

		boolean[] visited = new boolean[n];

		PriorityQueue<KeyValue> pq = new PriorityQueue<KeyValue>();
		pq.add(new KeyValue(0, 0));

		while(!pq.isEmpty()){
			KeyValue node = pq.remove();
			if (visited[node.key]) continue;

			minDist += distances[node.key];
			for (int i = 0; i < n; i++){
				if (!visited[i] && connectivity[node.key][i] != 0 && connectivity[node.key][i] < distances[i]){
					pq.add(new KeyValue(i, connectivity[node.key][i]));
					distances[i] = connectivity[node.key][i];
				}
			}
			visited[node.key] = true;
		}

		pw.println(minDist);
		pw.close();
	}

	static class KeyValue implements Comparable<KeyValue> {
		public int key;
		public int value;

		public KeyValue(int key, int value){
			this.key = key;
			this.value = value;
		}

		public int compareTo(KeyValue other){
			return value - other.value;
		}
	}
}