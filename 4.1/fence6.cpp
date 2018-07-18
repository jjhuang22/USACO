/*
ID: jonatha61
PROG: fence6
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <queue>

using namespace std;

const int MAX_VAL = 100000;

int distances[101][101], n, numV = 1;
map<set<int>, int> vertices;

int dijkstra(int start, int end) {
	int minDist[101];
	fill_n(minDist, 101, MAX_VAL);
	minDist[start] = 0;

	//(distance, node id)
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq; 
	pq.push(make_pair(0, start));

	while(pq.size()) {
		pair<int, int> node = pq.top(); pq.pop();
		if (minDist[node.second] == MAX_VAL) continue;

		// reached the end node
		if(node.second == end) {
			return minDist[node.second];
		}

		//relax all edges out of node
		for (int i = 1; i < numV; i++) {
			if (node.second != i && distances[node.second][i] != MAX_VAL) {
				if (minDist[i] > minDist[node.second] + distances[node.second][i]) {
					minDist[i] = minDist[node.second] + distances[node.second][i];
					pq.push(make_pair(minDist[i], i));
				}
			}
		}
	}

	return MAX_VAL;
}

int main() {
	ifstream fin ("fence6.in");
	ofstream fout ("fence6.out");
	fin >> n;
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			distances[i][j] = MAX_VAL;
		}
	}

	for (int i = 0; i < n; i++) {
		int s, l, n1, n2;
		fin >> s >> l >> n1 >> n2;
		set<int> s1, s2;
		s1.insert(s), s2.insert(s);
		for (int j = 0; j < n1; j++) {
			int e; fin >> e;
			s1.insert(e);
		}
		for (int j = 0; j < n2; j++) {
			int e; fin >> e;
			s2.insert(e);
		}

		//maintains set of vertices in graph
		if (vertices.find(s1) == vertices.end()) vertices[s1] = numV++;
		if (vertices.find(s2) == vertices.end()) vertices[s2] = numV++;
		distances[vertices[s1]][vertices[s2]] = distances[vertices[s2]][vertices[s1]] = l;
	}

	int ans = MAX_VAL;
	for (int i = 1; i < numV; i++) {
		for (int j = i + 1; j < numV; j++) {
			// ensures vertices are connected by single edge
			if (distances[i][j] != MAX_VAL) {

				int edgeWeight = distances[i][j];
				distances[i][j] = distances[j][i] = MAX_VAL;

				ans = min(ans, dijkstra(i, j) + edgeWeight);
				distances[i][j] = distances[j][i] = edgeWeight;
			}
		}
	}

	fout << ans << endl;
	return 0;
}