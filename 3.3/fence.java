/*
ID: jonatha61
LANG: JAVA
TASK: fence
*/

import java.io.*;
import java.util.*;

public class fence {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("fence.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("fence.out")));

		int f = Integer.parseInt(br.readLine());
		ArrayList<Integer>[] fences = new ArrayList[501];
		for (int i = 0; i < 501; i++) {
			fences[i] = new ArrayList<Integer>();
		}

		StringTokenizer st;
		for (int i = 0; i < f; i++) {
			st = new StringTokenizer(br.readLine());
			int i1 = Integer.parseInt(st.nextToken());
			int i2 = Integer.parseInt(st.nextToken());
			
			fences[i1].add(i2);
			fences[i2].add(i1);
		}

		for (int i = 1; i < 501; i++) {
			Collections.sort(fences[i]);
		}

		//find startNode
		int startNode = 1;
		for (int i = 1; i < 501; i++) {
			if (fences[i].size() % 2 == 1) {
				startNode = i;
				break;
			}
		}

		ArrayList<Integer> circuit = new ArrayList<Integer>();
		Stack<Integer> stack = new Stack<Integer>();
		int currLocation = startNode;

		while(circuit.size() < f + 1) {
			if (fences[currLocation].size() == 0) {
				circuit.add(currLocation);
				if (circuit.size() == f + 1) {
					break;
				} 
				currLocation = stack.pop();
			}

			else {
				int nextLocation = fences[currLocation].remove(0);
				fences[nextLocation].remove((Integer) currLocation);
				stack.push(currLocation);
				currLocation = nextLocation;
			}

		}

		for (int i = circuit.size() - 1; i >= 0; i--) {
			pw.println(circuit.get(i));
		}
		pw.close();
	}
}