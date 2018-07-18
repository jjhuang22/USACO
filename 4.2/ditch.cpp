/*
ID: jonatha61
PROG: ditch
LANG: C++11
*/

// Ford-Fulkerson using BFS
// some inputs may be repeats, make sure to add capacities

#include <fstream>
#include <queue>
#include <limits.h>

using namespace std;

int capacity[201][201], parent[201];
int n, m;
long long maxflow;

bool bfs(int source, int sink, int parent[]) {
	bool visited[201];
	for (int i = 0; i < 201; i++) {
		visited[i] = 0;
		parent[i] = 0;
	}

	queue<int> q;
	q.push(source);
	visited[source] = true;
	parent[source] = -1;

	while(!q.empty()) {
		int node = q.front(); q.pop();
		if (node == sink) return true;
		for (int i = 1; i <= m; i++) {
			if (!visited[i] && capacity[node][i] > 0) {
				q.push(i);
				parent[i] = node;
				visited[i] = true;
			}
		}
	}

	return (visited[sink] == true);
}

int main() {
	ifstream cin ("ditch.in");
	ofstream cout ("ditch.out");
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int s, e, c;
		cin >> s >> e >> c;
		capacity[s][e] += c;
	}

	while (bfs(1, m, parent)) {
		int path_flow = INT_MAX;

		//calculate min flow along path
		for (int v = m; v != 1; v = parent[v]) {
			int u = parent[v];
			path_flow = min(path_flow, capacity[u][v]);
		}

		//update residual graph
		for (int v = m; v != 1; v = parent[v]) {
			int u = parent[v];
			capacity[u][v] -= path_flow;
			capacity[v][u] += path_flow;
		}

		maxflow += path_flow;
	}

	cout << maxflow << endl;
	return 0;
}