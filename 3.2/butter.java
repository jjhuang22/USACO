/*
ID: jonatha61
LANG: JAVA
TASK: butter
*/

import java.io.*;
import java.util.*;

public class butter {
	static int[] cows;
	static int p;
	static int[][] paths;
	static ArrayList<ArrayList<Integer>> edges;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("butter.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("butter.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		p = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());

		cows = new int[n];
		for (int i = 0; i < n; i++) {
			cows[i] = Integer.parseInt(br.readLine());
		}

		paths = new int[p + 1][p + 1];
		for (int i = 0; i <= p; i++) {
			Arrays.fill(paths[i], Integer.MAX_VALUE);
			paths[i][i] = 0;
		}

		edges = new ArrayList<ArrayList<Integer>>();
		for (int i = 0; i <= p; i++) { 
			edges.add(new ArrayList<Integer>());
		}

		for (int i = 0; i < c; i++) { 
			st = new StringTokenizer(br.readLine());
			int p1 = Integer.parseInt(st.nextToken());
			int p2 = Integer.parseInt(st.nextToken());
			int distance = Integer.parseInt(st.nextToken());
			paths[p1][p2] = distance;
			paths[p2][p1] = distance;

			edges.get(p1).add(p2);
			edges.get(p2).add(p1);
		}

		int minDistance = Integer.MAX_VALUE;
		for (int i = 1; i <= p; i++) { 
			minDistance = Math.min(minDistance, dijkstra(i));
		}

		pw.println(minDistance);
		pw.close();
	}

	static int dijkstra (int root) { 
		Pasture[] pastures = new Pasture[p + 1];
		for (int i = 1; i <= p; i++) { 
			pastures[i] = new Pasture (i, Integer.MAX_VALUE, false);
		}

		PriorityQueue<Pasture> pq = new PriorityQueue<Pasture>();
		pastures[root] = new Pasture(root, 0, false);
		pq.add(pastures[root]);

		while(!pq.isEmpty()) {
			Pasture current = pq.remove();
			int id = current.id;

			if (pastures[id].visited) continue;
			pastures[id].visited = true;

			for (int i = 0; i < edges.get(id).size(); i++) {
				int nextNode = edges.get(id).get(i);				
				if (paths[id][nextNode] != Integer.MAX_VALUE && !pastures[nextNode].visited) { 
					pastures[nextNode].distance = Math.min(pastures[nextNode].distance, paths[id][nextNode] + pastures[id].distance);

					pq.add(pastures[nextNode]);
				}
			}
		}

		int distance = 0;
		for (int i = 0; i < cows.length; i++) {
			distance += pastures[cows[i]].distance;
		}
		return distance;
	}

	static class Pasture implements Comparable<Pasture> { 
		int id;
		int distance;
		boolean visited;

		public Pasture (int id, int distance, boolean visited) { 
			this.id = id;
			this.distance = distance;
			this.visited = visited;
		}

		public int compareTo (Pasture p) { 
			return distance - p.distance;
		}
	}
}