/*
ID: jonatha61
PROG: shuttle
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	ifstream cin ("shuttle.in");
	ofstream fout ("shuttle.out");
	int n; cin >> n;

	int currentLine = 0;
	int currentStart = n;
	int right = 1;
	bool expanding = true;

	while (true) {
		if (currentStart == n+1) break;
		if (right == 1) {
			for (int i = currentStart; i <= 2*n+2-currentStart; i+=2) {
				if (currentLine % 20 == 19) fout << i << endl;
				else fout << i << " ";
				currentLine++;
			}
		}

		else {
			for (int i = currentStart; i >= 2*n+2-currentStart; i-=2) {
				if (currentLine % 20 == 19) fout << i << endl;
				else fout << i << " ";
				currentLine++;
			}
		}

		currentStart = 2*n+2-currentStart;

		if (expanding && (currentStart == 1 || currentStart == 2*n+1)) expanding = false;
		else if (!expanding && currentStart >= n && currentStart <= n+2) break;

		if (expanding) {
			currentStart += right;
			right = -right;
		}
		else {
			right = -right;
			currentStart += right;
		}
	}
	fout << n+1 << endl;
	return 0;
}