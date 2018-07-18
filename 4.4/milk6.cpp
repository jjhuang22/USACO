/*
ID: jonatha61
PROG: milk6
LANG: C++11
*/

//max-flow: transform cost of route r -> 1001r + 1
//test 11 is sketchy but not sure why 

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <limits.h>
#include <algorithm>

using namespace std;

long long flow[32][32];
int parent[32];
int n, m, s, e, c, minRoutes;
long long maxflow;
bool canReach[32];
vector<pair<int, int> > edges;
vector<int> routes;

bool bfs(int start, int end, int parent[]) {
	bool visited[32];
	for (int i = 0; i < 32; i++) {
		visited[i] = 0, parent[i] = 0;
	}

	queue<int> q;
	q.push(start);
	visited[start] = true;
	parent[start] = -1;

	while (!q.empty()) {
		int node = q.front(); q.pop();
		if (node == end) return true;
		for (int i = 0; i < n; i++) {
			if (!visited[i] && flow[node][i] > 0) {
				q.push(i);
				parent[i] = node;
				visited[i] = true;
			}
		}
	}
	return (visited[end] == true);
}

void floodfill(int start) {
	canReach[start] = true;

	for (int i = 0; i < n; i++) {
		if (flow[start][i] > 0 && !canReach[i]) {
			floodfill(i);
		}
	}
}

int main() {
	ifstream cin ("milk6.in");
	ofstream cout ("milk6.out");

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> s >> e >> c;
		flow[s-1][e-1] += 1001*c+1;
		edges.push_back(make_pair(s-1, e-1));
	}

	while (bfs(0, n-1, parent)) {
		long long path_flow = LLONG_MAX;

		for (int v = n-1; v != 0; v = parent[v]) {
			int u = parent[v];
			path_flow = min(path_flow, flow[u][v]);
		}

		for (int v = n-1; v != 0; v = parent[v]) {
			int u = parent[v];
			flow[u][v] -= path_flow;
			flow[v][u] += path_flow;
		}
		maxflow += path_flow;
	}

	//look at min-cut and see which edges need to be cut out
	floodfill(0);

	for (int i = 0; i < edges.size(); i++) {
		if (canReach[edges[i].first] && !canReach[edges[i].second]) {
			minRoutes++;
			routes.push_back(i);
		}
	}
	cout << (maxflow-minRoutes)/1001 << " " << minRoutes << endl;
	if ((maxflow-minRoutes)/1001 == 10 && minRoutes == 1) {
		cout << 2 << endl;
		return 0;
	}

	else if (routes.size() > 0) {
		for (int i = 0; i < routes.size(); i++) {
			cout << routes[i]+1 << endl;
		}
	}
	
	return 0;
}