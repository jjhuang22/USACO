/*
ID: jonatha61
PROG: bigbrn
LANG: C++11
*/

//lol DP 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int grid[1001][1001];
int ans;

int main() {
	ifstream cin ("bigbrn.in");
	ofstream cout ("bigbrn.out");

	int n, t; cin >> n >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			grid[i][j] = 1;
		}
	}

	int x, y;
	for (int i = 0; i < t; i++) {
		cin >> x >> y;
		grid[x][y] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (grid[i][j] != 0) {
				grid[i][j] = 1 + min(grid[i-1][j-1], min(grid[i-1][j], grid[i][j-1]));
				ans = max(ans, grid[i][j]);
			}
		}
	}

	cout << ans << endl;
	return 0;
}