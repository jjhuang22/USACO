/*
ID: jonatha61
PROG: stall4
LANG: C++11
*/

// maximum matching - maxflow
// source - 0, cows - (1, n), stalls - (n+1, n+m), sink - n+m+1

#include <iostream>
#include <fstream>
#include <queue>
#include <limits.h>

using namespace std;

int network[402][402], parent[402];
int n, m;
long long maxflow;

bool bfs(int source, int sink, int parent[]) {
	bool visited[402];
	for (int i = 0; i < 402; i++) {
		visited[i] = 0;
		parent[i] = -1;
	}

	queue<int> q;
	q.push(source);
	visited[source] = true;

	while(!q.empty()) {
		int node = q.front(); q.pop();
		if (node == sink) return true;

		for (int i = 0; i <= n+m+1; i++) {
			if (!visited[i] && network[node][i] == 1) {
				//cout << i << endl;
				q.push(i);
				parent[i] = node;
				visited[i] = true;
			}
		}
	}

	return (visited[sink] == true);
}

int main() {
	ifstream cin ("stall4.in");
	ofstream cout ("stall4.out");
	cin >> n >> m;

	for (int i = 1; i <= n; i++) network[0][i] = 1;
	for (int i = n+1; i <= n+m; i++) network[i][n+m+1] = 1;
	for (int i = 1; i <= n; i++) {
		int s;
		cin >> s;
		for (int j = 0; j < s; j++) {
			int x;
			cin >> x;
			network[i][x+n] = 1;
		}
	}

	while(bfs(0, n+m+1, parent)) {
		int path_flow = INT_MAX;

		for (int v = n+m+1; v != 0; v = parent[v]) {
			int u = parent[v];
			path_flow = min(path_flow, network[u][v]);
		}

		for (int v = n+m+1; v != 0; v = parent[v]) {
			int u = parent[v];
			network[u][v] -= path_flow;
			network[v][u] += path_flow;
		}

		maxflow += path_flow;
	}

	cout << maxflow << endl;	
	return 0;
}