/*
ID: jonatha61
LANG: JAVA
TASK: heritage
*/

import java.io.*;
import java.util.*;

public class heritage {
	static PrintWriter pw;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("heritage.in"));
		pw = new PrintWriter(new BufferedWriter(new FileWriter("heritage.out")));

		String inOrder = br.readLine();
		String preOrder = br.readLine();

		printPostOrder(inOrder, preOrder);
		pw.println();
		pw.close();
	}

	static void printPostOrder(String inOrder, String preOrder) {
		if (inOrder.length() < 2) {
			pw.print(inOrder);
			return;
		} 

		String root = preOrder.substring(0, 1);

		printPostOrder(inOrder.substring(0, inOrder.indexOf(root)), preOrder.substring(1, 1 + inOrder.indexOf(root)));
		printPostOrder(inOrder.substring(inOrder.indexOf(root) + 1), preOrder.substring(inOrder.indexOf(root) + 1));
		pw.print(root);
	}
}