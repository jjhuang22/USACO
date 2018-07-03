/*
ID: jonatha61
LANG: JAVA
TASK: contact
*/

import java.io.*;
import java.util.*;

public class contact {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("contact.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("contact.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());

		StringBuilder sb = new StringBuilder();
		String nextLine;
		while ((nextLine = br.readLine()) != null) {
			sb.append(nextLine);
		}

		String input = sb.toString();

		HashMap<String, Integer> map = new HashMap<String, Integer>();
		for (int i = a; i <= b; i++) {
			for (int j = 0; j + i <= input.length(); j++) {
				String subPattern = input.substring(j, j + i);
				if (!map.containsKey(subPattern)){
					map.put(subPattern, 0);
				}
				map.put(subPattern, map.get(subPattern) + 1);
			}	
		} 

		// convert hashmap to ArrayList
		ArrayList<Pattern> patterns = new ArrayList<Pattern>();
		for (String s : map.keySet()){
			patterns.add(new Pattern(s, map.get(s)));
		}

		Collections.sort(patterns);

		//print out most frequent patterns
		int counter = 1;
		int currentFreq = patterns.get(0).freq;
		pw.println(currentFreq);

		int currentLineCounter = 1;
		String currentLine = patterns.get(0).pat + " ";

		for (int i = 1; i < patterns.size() && counter <= n; i++) {
			Pattern nextPattern = patterns.get(i);

			//new frequency
			if (nextPattern.freq != currentFreq) {
				counter++;
				if (counter > n) break;
				if (currentLine.trim() != "") {
					pw.println(currentLine.trim());
				}

				currentFreq = nextPattern.freq;
				pw.println(nextPattern.freq);

				currentLine = "";
				currentLine += nextPattern.pat + " ";
				currentLineCounter = 1;
			}

			else {
				if (currentLineCounter == 6){
					pw.println(currentLine.trim());
					currentLine = "";
					currentLineCounter = 1;
					currentLine += nextPattern.pat + " ";
				}
				else{
					currentLine += nextPattern.pat + " ";
					currentLineCounter++;
				}
			}
	
		}
		pw.println(currentLine.trim());
		pw.close();
	}

	static class Pattern implements Comparable<Pattern> {
		String pat;
		int freq;

		public Pattern(String pat, int freq) {
			this.pat = pat;
			this.freq = freq;
		}

		public int compareTo(Pattern o) {
			if (freq != o.freq) {
				return o.freq - freq;
			}

			if (pat.length() != o.pat.length()){
				return pat.length() - o.pat.length();
			}

			return Integer.parseInt(pat, 2) - Integer.parseInt(o.pat, 2);		
		}

		public String toString() {
			return "Pattern: " + pat + "Frequency: " + freq;
		}
	}
}