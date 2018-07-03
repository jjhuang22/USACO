/*
ID: jonatha61
LANG: JAVA
TASK: shopping
*/

/* DP. Really nasty to code up */

import java.io.*;
import java.util.*;

public class shopping {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("shopping.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("shopping.out")));

		int s = Integer.parseInt(br.readLine());
		StringTokenizer st;

		Offer[] offers = new Offer[100];
		for (int i = 0; i < 100; i++) {
			offers[i] = new Offer();
			offers[i].products = new Product[6];
			for (int j = 0; j < 6; j++) {
				offers[i].products[j] = new Product();
			}
		}
		int[] hash = new int[1000];
		int[] numItems = new int[6];
		int[] prices = new int[6];
		int[][][][][] dp = new int[6][6][6][6][6];

		for (int i = 1; i <= s; i++) {
			st = new StringTokenizer(br.readLine());

			offers[i].numProducts = Integer.parseInt(st.nextToken());
			for (int j = 1; j <= offers[i].numProducts; j++) {
				offers[i].products[j].code = Integer.parseInt(st.nextToken());
				offers[i].products[j].numItems = Integer.parseInt(st.nextToken());
			}

			offers[i].price = Integer.parseInt(st.nextToken());
		}

		int B = Integer.parseInt(br.readLine());
		for (int i = 1; i <= B; i++) {
			st = new StringTokenizer(br.readLine());
			int code = Integer.parseInt(st.nextToken());
			hash[code] = i;

			numItems[i] = Integer.parseInt(st.nextToken());
			prices[i] = Integer.parseInt(st.nextToken());
		}

		// loop through all configurations
		for (int a = 0; a <= numItems[1]; a++) {
			for (int b = 0; b <= numItems[2]; b++) {
				for (int c = 0; c <= numItems[3]; c++) {
					for (int d = 0; d <= numItems[4]; d++) {
						for (int e = 0; e <= numItems[5]; e++) {
							if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0) continue;

							int normalPrice = a * prices[1] + b * prices[2] + c * prices[3] + d * prices[4] + e * prices[5];


							//loop through all the offers
							for (int i = 1; i <= s; i++) {
								int[] itemsInOffer = new int[6];
								for (int j = 1; j <= offers[i].numProducts; j++) {
									itemsInOffer[hash[offers[i].products[j].code]] = offers[i].products[j].numItems;
								}

								if (itemsInOffer[1] > a || itemsInOffer[2] > b || itemsInOffer[3] > c || itemsInOffer[4] > d || itemsInOffer[5] > e) {
									continue;
								}

								normalPrice = Math.min(normalPrice, offers[i].price + dp[a - itemsInOffer[1]][b - itemsInOffer[2]][c - itemsInOffer[3]][d - itemsInOffer[4]][e - itemsInOffer[5]]);
							}

							dp[a][b][c][d][e] = normalPrice;
						}
					}
				}
			}
		}

		pw.println(dp[numItems[1]][numItems[2]][numItems[3]][numItems[4]][numItems[5]]);
		pw.close();
	}

	static class Offer {
		int numProducts;
		int price;
		Product[] products;

		public Offer () {
			numProducts = 0;
			price = 0;
			Product[] products = new Product[6];
		}
	}

	static class Product {
		int code;
		int numItems;

		public Product () {
			code = 0;
			numItems = 0;
		}

		public Product (int code, int numItems) {
			this.code = code;
			this.numItems = numItems;
		}
	}
}