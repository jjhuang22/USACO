/*
ID: jonatha61
PROG: milk4
LANG: C++11
*/

// DP + backtracking + recursion


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <cstring>

using namespace std;

int q, p;
int pails[100], optimalPails[100];
int dp[20001];
ifstream fin ("milk4.in");
ofstream fout ("milk4.out");

//dp function
bool possible(int maxPailsUsed) {
	if (maxPailsUsed == 1) return q % optimalPails[0] == 0;
	if (maxPailsUsed == 2) {
		int qcopy = q;
		while (qcopy > 0) {
			if (qcopy % optimalPails[0] == 0) return true;
			qcopy -= optimalPails[1];
		}
		return false;
	}

	memset(dp, 0, sizeof(dp));
	dp[0] = true;
	for (int i = 0; i < maxPailsUsed; i++) {
		for (int j = 0; j <= q - optimalPails[i]; j++) {
			if (dp[j]) dp[j + optimalPails[i]] = true;
			if (dp[q]) return true;
		}
	}

	return false;
}

bool search(int currPailsUsed, int nextPail, int maxPailsUsed) {
	if (currPailsUsed == maxPailsUsed) {
		if (possible(maxPailsUsed)) {
			fout << maxPailsUsed;
			for (int i = 0; i < maxPailsUsed; i++) {
				fout << " " << optimalPails[i];
			}
			fout << "\n";
			return true;
		}
		return false;
	}


	for (int i = nextPail; i <= p - (maxPailsUsed - currPailsUsed); i++) {
		optimalPails[currPailsUsed] = pails[i];
		if (search(currPailsUsed + 1, i + 1, maxPailsUsed)) return true;
	}
	return false;
}

int main() {
	fin >> q >> p;
	for (int i = 0; i < p; i++) {
		fin >> pails[i];
	}
	sort(pails, pails + p);

	for (int i = 1; i <= p; i++) {
		if (search(0, 0, i)) break;
	}
	return 0;
}