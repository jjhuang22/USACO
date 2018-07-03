/*
ID: jonatha61
LANG: JAVA
TASK: humble
*/

import java.io.*;
import java.util.*;

public class humble {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("humble.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("humble.out")));

		StringTokenizer st = new StringTokenizer(br.readLine());
		int k = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());

		int[] primes = new int[k];
		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < k; i++){
			primes[i] = Integer.parseInt(st.nextToken());
		}

		//array to hold first n humble numbers
		long[] humbleNums = new long[n+1];
		humbleNums[0] = 1;

		//holds first index to check for each prime number
		int[] lastIndex = new int[k];

		for (int i = 1; i <= n; i++){
			long mustExceed = humbleNums[i - 1];

			PriorityQueue<Long> pq = new PriorityQueue<Long>();
			for (int j = 0; j < k; j++){
				while(primes[j] * humbleNums[lastIndex[j]] <= mustExceed){
					lastIndex[j]++;
				}
				pq.add(primes[j] * humbleNums[lastIndex[j]]);
			}

			humbleNums[i] = pq.remove();
		}

		pw.println(humbleNums[n]);
		pw.close();
	}
}