/*
ID: jonatha61
PROG: race3
LANG: C++11
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;

int mat[50][50], n, unavoidable, splitting;
int visited[50], revisited[50], unavoidPts[50], splitPts[50];

void floodfill(int point) {
	if (point == n) {
		visited[n] = 1;
		return;
	}
	if (visited[point]) return;
	visited[point] = 1;
	for (int i = 0; i <= n; i++) {
		if (mat[point][i]) floodfill(i);
	}
}

int main() {
	ifstream cin ("race3.in");
	ofstream cout ("race3.out");

	int input;
	while(true) {
		cin >> input;
		if (input == -2) n++;
		else if (input == -1) break;
		else mat[n][input] = 1;
	}
	n--;

	//part 1: floodfill to find unavoidable locations
	for (int i = 1; i < n; i++) {
		memset(visited, 0, sizeof(visited));
		visited[i] = 1;
		floodfill(0);

		if (!visited[n]) {
			unavoidPts[i] = 1;
			unavoidable++;
		}
	}

	cout << unavoidable;
	for (int i = 1; i < n; i++) {
		if (unavoidPts[i]) cout << " " << i;
	}
	cout << "\n";

	//part 2: floodfill to find splitting locations
	for (int i = 1; i < n; i++) {
		if (unavoidPts[i]) {
			memset(visited, 0, sizeof(visited));
			floodfill(i);
			memcpy(revisited, visited, sizeof(revisited));

			memset(visited, 0, sizeof(visited));
			visited[i] = 1;
			floodfill(0);

			int j = 0;
			while (j <= n) {
				if (visited[j] && revisited[j] && i != j) break;
				j++;
			}

			if (j > n) {
				splitting++;
				splitPts[i] = 1;
			}
		}
	}

	cout << splitting;
	for (int i = 1; i < n; i++) {
		if (splitPts[i]) cout << " " << i;
	}
	cout << "\n";
	return 0;
}