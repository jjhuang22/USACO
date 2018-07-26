/*
ID: jonatha61
PROG: telecow
LANG: C++11
*/

//min-cut maxflow
//code to determine min-cut is extremely messy and unelegant :(
//should try determining min-cut by looking at edges

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <queue>
#include <set>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <limits.h>

using namespace std;

const int MAXN = 203;

int n, m, c1, c2;
int network1[MAXN][MAXN];
int network2[MAXN][MAXN];
int parent[MAXN];
bool minCut[MAXN];
// vector<int> edges[MAXN];
// vector<pair<int, int> > edges;
// bool floodVisited[MAXN];

// void floodfill(int start) {
// 	if (floodVisited[start]) return;
// 	floodVisited[start] = 1;

// 	for (int i = 2; i <= 2*n + 1; i++) {
// 		if (!floodVisited[i] && network[start][i] > 0) {
// 			floodfill(i);
// 		}
// 	}
// }

bool bfs(int start, int end, int parent[], int network[MAXN][MAXN]) {
	bool visited[MAXN];
	for (int i = 0; i < MAXN; i++) {
		parent[i] = -1;
		visited[i] = 0;
	}

	queue<int> q;
	q.push(start);
	visited[start] = true;

	while(!q.empty()) {
		int node = q.front(); q.pop();
		if (node == end) return true;
		for (int i = 2; i <= 2*n+1; i++) {
			if (!visited[i] && network[node][i] > 0) {
				q.push(i);
				parent[i] = node;
				visited[i] = true;
			}
		}
	}

	return (visited[end] == true);
}

int maxflow(int network[MAXN][MAXN]) {
	int ans = 0;
	while(bfs(2*c1, 2*c2+1, parent, network)) {
		int path_flow = INT_MAX;
		for (int v = 2*c2+1; v != 2*c1; v = parent[v]) {
			int u = parent[v];
			path_flow = min(path_flow, network[u][v]);
		}

		for (int v = 2*c2+1; v != 2*c1; v = parent[v]) {
			int u = parent[v];
			network[u][v] -= path_flow;
			network[v][u] += path_flow;
		}

		ans += path_flow;
	}
	return ans;
}

int main() {
	ifstream cin ("telecow.in");
	ofstream cout ("telecow.out");

	cin >> n >> m >> c1 >> c2;

	//represent each computer as in (2i+1) and out (2i) node
	for (int i = 1; i <= n; i++) {
		network1[2*i][2*i+1] = network1[2*i+1][2*i] = 1;
		network2[2*i][2*i+1] = network2[2*i+1][2*i] = 1;
		// edges[2*i].push_back(2*i+1);
		// edges[2*i+1].push_back(2*i);
		// edges.push_back(make_pair(2*i, 2*i+1));
	}

	//input - give connected computers "very large" capacity
	int a, b; 
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		network1[2*a][2*b+1] = network1[2*b][2*a+1] = MAXN;
		network2[2*a][2*b+1] = network2[2*b][2*a+1] = MAXN;
		// edges[2*a].push_back(2*b+1);
		// edges[2*b].push_back(2*a+1);
		// edges.push_back(make_pair(2*a, 2*b+1));
		// edges.push_back(make_pair(2*b, 2*a+1));
	}

	int minCowputers = maxflow(network1);
	cout << minCowputers << endl;

	//shut down computers one by one
	for (int i = 1; i <= n; i++) {
		if (i == c1 || i == c2) continue;
		int tempNetwork[MAXN][MAXN];
		for (int j = 0; j < MAXN; j++) for (int k = 0; k < MAXN; k++) tempNetwork[j][k] = network2[j][k];

		for (int j = 0; j < MAXN; j++) {
			tempNetwork[2*i][j] = 0;
			tempNetwork[2*i+1][j] = 0;
		}

		int tempAns = maxflow(tempNetwork);
		if (tempAns < minCowputers) {
			minCut[i] = 1;
			minCowputers = tempAns;
			memset(network2[2*i], 0, sizeof(network2[2*i]));
			memset(network2[2*i+1], 0, sizeof(network2[2*i+1]));
		}
	}

	bool first = false;
	for (int i = 1; i <= n; i++) {
		if (minCut[i]) {
			if (!first) {
				cout << i;
				first = true;
			}
			else {
				cout << " " << i;
			}
		}
	}
	cout << "\n";
	return 0;
}