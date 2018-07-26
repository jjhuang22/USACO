/*
ID: jonatha61
PROG: charrec
LANG: C++11
*/

//DP

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <limits.h>

using namespace std;

char font[27][21][21];
char input[1201][21];
int dp[1201];
string ans[1201];

int missing(char a[][21], char b[][21]) {
	int diff = INT_MAX;

	for (int i = 0; i < 20; i++) {
		int temp = 0;
		int p1 = 0, p2 = 0;
		while (p1 < 20) {
			if (p1 == i) {
				p1++;
				continue;
			}
			for (int j = 0; j < 20; j++) {
				if (a[p1][j] != b[p2][j]) {
					temp++;
				}
			}
			if (temp >= diff) break;
			p1++; 
			p2++;
		}
		diff = min(diff, temp);
	}
	return diff;
}

int change(char a[][21], char b[][21]) {
	int diff = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (a[i][j] != b[i][j]) diff++;
		}
	}
	return diff;
}

int duplicate(char a[][21], char b[][21]) {
	int diff = INT_MAX;

	for (int i = 0; i <= 20; i++) {
		int temp = 0;
		int p1 = 0, p2 = 0;
		while (p1 < 20) {
			if (p2 == i) {
				p2++;
				continue;
			}
			for (int j = 0; j < 20; j++) {
				if (a[p1][j] != b[p2][j]) {
					temp++;
				}
			}
			p1++; 
			p2++;
			if (temp >= diff) break;	
		}
		diff = min(diff, temp);
	}
	return diff;
}

char getChar(int j) {
	if (j == 0) return ' ';
	else return (char)('a' + j - 1);
}

int main() {
	ifstream fin ("font.in");
	ifstream cin ("charrec.in");
	ofstream cout ("charrec.out");

	int n; fin >> n;
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 20; j++) {
			for (int k = 0; k < 20; k++) {
				fin >> font[i][j][k];
			}
		}
	}

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 20; j++) {
			cin >> input[i][j];
		}
	}

	for (int i = 1; i <= n; i++) dp[i] = INT_MAX;

	for (int i = 1; i <= n; i++) {
		if (i >= 19 && dp[i-19] < dp[i]) {
			for (int j = 0; j < 27; j++) {

				int diff = missing(font[j], &(input[i-18]));
				if (diff > 120 || dp[i-19] + diff >= dp[i]) continue;
				dp[i] = dp[i-19] + diff;

				ans[i] = ans[i-19] + getChar(j);
			}
		}

		if (i >= 20 && dp[i-20] < dp[i]) {
			for (int j = 0; j < 27; j++) {
				int diff = change(font[j], &(input[i-19]));
				if (diff > 120 || dp[i-20] + diff >= dp[i]) continue;
				dp[i] = dp[i-20] + diff;
				
				ans[i] = ans[i-20] + getChar(j);
			}
		}

		if (i >= 21 && dp[i-21] < dp[i]) {
			for (int j = 0; j < 27; j++) {
				int diff = duplicate(font[j], &(input[i-20]));
				if (diff > 120 || dp[i-21] + diff >= dp[i]) continue;
				dp[i] = dp[i-21] + diff;
				
				ans[i] = ans[i-21] + getChar(j);
			}
		}
	}

	cout << ans[n] << endl;
	return 0;
}