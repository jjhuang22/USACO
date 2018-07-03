/*
ID: jonatha61
LANG: JAVA
TASK: fact4
*/

import java.io.*;
import java.util.*;

public class fact4 {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("fact4.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("fact4.out")));

		int n = Integer.parseInt(br.readLine());
		int lastDigit = 1;
		int num2 = 0;
		int num5 = 0;
		for (int i = 2; i <= n; i++){
			int temp = i;
			while (temp % 2 == 0) {
				num2++;
				temp /= 2;
			}
			while(temp % 5 == 0) {
				num5++;
				temp /= 5;
			}

			lastDigit = (lastDigit * temp) % 10;
		}
		
		for (int i = 0; i < num2 - num5; i++){
				lastDigit = (lastDigit * 2) % 10;
		}
		pw.println(lastDigit);
		pw.close();
	}
}