/*
ID: jonatha61
PROG: twofive
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <map>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

int x[26], y[26];
int dp[6][6][6][6][6];

void process() {
	dp[0][0][0][0][0] = 1;
	for (int e = 0; e <= 5; e++) {
		for (int d = e; d <= 5; d++) {
			for (int c = d; c <= 5; c++) {
				for (int b = c; b <= 5; b++) {
					for (int a = b; a <= 5; a++) {
						long total = 0;
						
						if (a > 0) total += dp[a-1][b][c][d][e];
						if (b > 0) total += dp[a][b-1][c][d][e];
						if (c > 0) total += dp[a][b][c-1][d][e];
						if (d > 0) total += dp[a][b][c][d-1][e];
						if (e > 0) total += dp[a][b][c][d][e-1];

						dp[a][b][c][d][e] += total;
					}
				}
			}
		}
	}
}

void getString(int n) {
	
}

void getNum(string s) {

}

int main() {
	ifstream cin ("twofive.in");
	ofstream fout ("twofive.out");

	char c; cin >> c;
	process();
	if (c == 'N') {
		int n; cin >> n;
		getString(n);
	}
	else if (c == 'W') {
		string s; cin >> s;
		getNum(s);
	}
	
	return 0;
}