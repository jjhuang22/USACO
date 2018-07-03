/*
ID: jonatha61
LANG: JAVA
TASK: msquare
*/

import java.io.*;
import java.util.*;

public class msquare {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("msquare.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("msquare.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < 8; i++) { 
			sb.append(st.nextToken());
		}

		String input = sb.toString();
		String targetString = input.substring(0, 4) + 
					   input.substring(7) + 
					   input.substring(6, 7) +
					   input.substring(5, 6) +
					   input.substring(4, 5);

		State target = new State(targetString, "");

		HashSet<String> visited = new HashSet<String>();

		Queue<State> q = new LinkedList<State>();
		State initialState = new State("12348765", "");
		q.add(initialState);

		while(!q.isEmpty()) {
			State currentState = q.remove();
			if (visited.contains(currentState.pat)) continue;
			visited.add(currentState.pat);

			if (currentState.pat.equals(target.pat)) {
				pw.println(currentState.seq.length());
				pw.println(currentState.seq);
				break;
			}

			else {
				q.add(currentState.transformA());
				q.add(currentState.transformB());
				q.add(currentState.transformC());
			}
		}

		pw.close();
	}

	static class State { 
		String pat;
		String seq;

		public State (String p, String s) {
			pat = p;
			seq = s;
		}

		public State transformA () {
			String newString = "";
			newString = pat.substring(4) + pat.substring(0,4);
			return new State(newString, this.seq + "A");
		}

		public State transformB () {
			String newString = "";
			newString = pat.substring(3, 4) + pat.substring(0, 3) + pat.substring(7) + pat.substring(4, 7);
			return new State(newString, this.seq + "B");
		}

		public State transformC () {
			String newString = "";
			newString = pat.substring(0, 1) + pat.substring(5, 6) + 
						pat.substring(1, 2) + pat.substring(3, 5) + 
						pat.substring(6, 7) + pat.substring(2, 3) + pat.substring(7);
			return new State(newString, this.seq + "C");
		}

		public String toString () {
			return pat.substring(0, 4) + "\n" + pat.substring(4);
		}
	}
}