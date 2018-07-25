/*
ID: jonatha61
PROG: starry
LANG: C++11
*/

// floodfill
// sky is the original board, visited is the set of points in the original board that are currently being searched
// currCluster is the cut-out version of the current cluster

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <cstring>

using namespace std;

#define f first
#define s second

const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int w, h, numClusters;
int minX, maxX, minY, maxY;
char sky[100][100];
int ans[100][100];
bool visited[100][100];
bool currCluster[100][100];
bool clusters[26][100][100];
pair<int, int> size[26];


void floodfill(int x, int y) {
	if (x < 0 || x >= h || y < 0 || y >= w) return;
	if (visited[x][y] || sky[x][y] != '1') return;
	visited[x][y] = true;
	minX = min(minX, x);
	minY = min(minY, y);
	maxX = max(maxX, x);
	maxY = max(maxY, y);

	for (int i = 0; i < 8; i++) {
		floodfill(x + dx[i], y + dy[i]);
	}
}

bool match(int k) {
	if (size[k].f == maxX - minX && size[k].s == maxY - minY) {
		//original orientation
		bool same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][i][j]);
			}
		}
		if (same) return true;

		//flip about x-axis
		same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][maxX - minX -i][j]);
			}
		}
		if (same) return true;

		//flip about y-axis
		same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][i][maxY - minY - j]);
			}
		}
		if (same) return true;

		//flip about both axes
		same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][maxX - minX - i][maxY - minY - j]);
			}
		}
		if (same) return true;

	}

	if (size[k].s == maxX - minX && size[k].f == maxY - minY) {
		//90 degree clockwise 
		bool same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][j][maxX - minX - i]);
			}
		}
		if (same) return true;

		//90 degree clockwise and flip about y-axis
		same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][j][i]);
			}
		}
		if (same) return true;


		//90 degree counterclockwise
		same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][maxY - minY - j][i]);
			}
		}
		if (same) return true;

		//90 degree counterclockwise and flip about y-axis
		same = true;
		for (int i = 0; i <= maxX - minX; i++) {
			for (int j = 0; j <= maxY - minY; j++) {
				same &= (currCluster[i][j] == clusters[k][maxY - minY - j][maxX - minX - i]);
			}
		}
		if (same) return true;
	}
	return false;
}

int main() {
	ifstream cin ("starry.in");
	ofstream cout ("starry.out");

	cin >> w >> h;
	string row;
	for (int i = 0; i < h; i++) {
		cin >> row;
		for (int j = 0; j < w; j++) {
			sky[i][j] = row[j];
		}
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			// start by floodfilling 
			if (sky[i][j] == '1') {
				memset(visited, 0, sizeof(visited));
				minX = h;
				maxX = 0;
				minY = w;
				maxY = 0;
				floodfill(i, j);

				memset(currCluster, 0, sizeof(currCluster));
				//fill out currCluster for comparison
				for (int k = 0; k <= maxX - minX; k++) {
					for (int l = 0; l <= maxY - minY; l++) {
						currCluster[k][l] = visited[k + minX][l + minY];
					}
				}

				// check to see if currCluster is similar to previous clusters
				int k = 0;
				for (k = 0; k < numClusters; k++) {
					if (match(k)) break;
				}

				if (k == numClusters) {
					numClusters++;
					for (int l = 0; l <= maxX - minX; l++) {
						for (int m = 0; m <= maxY - minY; m++) {
							clusters[k][l][m] = currCluster[l][m];
						}
					}
					size[k] = make_pair(maxX - minX, maxY - minY);
				}


				//start indexing with 2 to avoid conflicts with 1 and 0 in original grid
				for (int l = 0; l <= maxX - minX; l++) {
					for (int m = 0; m <= maxY - minY; m++) {
						if (currCluster[l][m]) {
							ans[l + minX][m + minY] = k + 2;
						}
					}
				}
			}

			
		}
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (ans[i][j] > 1) {
				cout << (char)(ans[i][j] - 2 + 'a');
			}
			else cout << 0;
		}
		cout << endl;
	}

	return 0;
}