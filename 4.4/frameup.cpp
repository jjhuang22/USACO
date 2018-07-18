/*
ID: jonatha61
PROG: frameup
LANG: C++11
*/

//use recursion to backtrack 

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <limits.h>
#include <algorithm>

using namespace std;

char board[30][30];
int boundaries[26][4];
int seen[26];
int order[26][26];
int numChars;
char answer[27];

void solve(int start, ofstream &cout) {
	if (start == numChars) {
		answer[start] = '\0';
		cout << answer << endl;
		return;
	}

	for (int i = 0; i < 26; i++) {
		if (seen[i]) {

			int j;
			for (j = 0; j < 26; j++) {
				if (seen[j] && order[i][j]) break;
			}

			if (j >= 26) {
				answer[start] = 'A' + i;
				seen[i] = 0;
				solve(start+1, cout);
				seen[i] = 1;
			}
		}
	}
}

int main() {
	ifstream cin ("frameup.in");
	ofstream cout ("frameup.out");

	int h, w; cin >> h >> w;
	string s;
	for (int i = 0; i < h; i++) {
		cin >> s;
		for (int j = 0; j < w; j++) {
			board[i][j] = s[j];
		}
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (board[i][j] != '.') {
				int num = board[i][j] - 'A';
				if (!seen[num]) {
					numChars++;
					seen[num] = 1;
					boundaries[num][0] = boundaries[num][2] = i;
					boundaries[num][1] = boundaries[num][3] = j;
				}

				else {
					if (i < boundaries[num][0]) boundaries[num][0] = i;
					if (i > boundaries[num][2]) boundaries[num][2] = i;
					if (j < boundaries[num][1]) boundaries[num][1] = j;
					if (j > boundaries[num][3]) boundaries[num][3] = j;
				}
			}
		}
	}

	for (int i = 0; i < 26; i++) {
		if (seen[i]) {
			for (int j = boundaries[i][0]; j <= boundaries[i][2]; j++) {
				int num = board[j][boundaries[i][1]] - 'A';
				if (num != i) order[num][i] = 1;

				num = board[j][boundaries[i][3]] - 'A';
				if (num != i) order[num][i] = 1;
			}

			for (int j = boundaries[i][1]; j <= boundaries[i][3]; j++) {
				int num = board[boundaries[i][0]][j] - 'A';
				if (num != i) order[num][i] = 1;

				num = board[boundaries[i][2]][j] - 'A';
				if (num != i) order[num][i] = 1;

			}
		}
	}

	// for (int i = 0; i < 5; i++) {
	// 	for (int j = 0; j < 5; j++) {
	// 		cout << order[i][j];
	// 	}
	// 	cout << "\n";
	// }

	solve(0, cout);
	return 0;
}