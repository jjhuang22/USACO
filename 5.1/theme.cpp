/*
ID: jonatha61
PROG: theme
LANG: C++11
*/

// DP 
// because of memory limits, we do the for loops in a different way

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {
	ifstream cin ("theme.in");
	ofstream cout ("theme.out");

	int n; cin >> n;
	int notes[n];
	for (int i = 0; i < n; i++) {
		cin >> notes[i];
	}
	int ans = 1;

	for (int j = 1; j < n; j++) {
		int currLength = 1;
		for (int i = n - j - 1; i >= 0; i--) {
			if (notes[i] - notes[i+1] == notes[j+i] - notes[j+i+1]) {
				currLength++;
				currLength = min(currLength, j);
				ans = max(ans, currLength);
			}
			else currLength = 1;
		}
	}

	cout << (ans >= 5 ? ans : 0) << endl;
	return 0;
}