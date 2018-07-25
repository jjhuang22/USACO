/*
ID: jonatha61
PROG: snail
LANG: C++11
*/

// DFS

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

int n;
int square[120][120];
int visited[120][120];
int best, currCount;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool isValid(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n && square[x][y] == 0;
}

void dfs(int x, int y, int dir) {
	if (visited[x][y] == 1) {
		best = max(best, currCount);
		return;
	}
	visited[x][y] = 1;
	currCount++;
	best = max(best, currCount);
	if (isValid(x + dx[dir], y + dy[dir])) dfs(x + dx[dir], y + dy[dir], dir);
	else {
		int dir1 = (dir + 1) % 4;
		int dir2 = (dir + 3) % 4;
		if (isValid(x + dx[dir1], y + dy[dir1])) {
			//cout << x + dx[dir1] << " " << y + dy[dir1] << endl;
			dfs(x + dx[dir1], y + dy[dir1], dir1);

		}
		if (isValid(x + dx[dir2], y + dy[dir2])) {
			//cout << x + dx[dir2] << " " << y + dy[dir2] << endl;

			dfs(x + dx[dir2], y + dy[dir2], dir2);
		}

	}
	visited[x][y] = 0;
	currCount--;
}

int main() {
	ifstream cin ("snail.in");
	ofstream cout ("snail.out");

	int b; cin >> n >> b;
	char grid;
	int num;
	for (int i = 0; i < b; i++) {
		cin >> grid >> num;
		square[num-1][grid-'A'] = 1;
	}

	dfs(0, 0, 1);
	dfs(0, 0, 0);

	cout << best << endl;
	return 0;
}