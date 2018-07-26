/*
ID: jonatha61
PROG: schlnet
LANG: C++11
*/

//floodfill + dfs + related to SCC

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <map>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

bool network[101][101];
bool willReceive[101]; //needs to receive software
bool canReceive[101]; //can receive software from other schools
bool visited[101];
int sizeA, sizeB, n;

void dfs(int start) {
	if (visited[start]) return;
	visited[start] = 1;
	willReceive[start] = 0;
	canReceive[start] = 1;
	for (int i = 1; i <= n; i++) {
		if (network[start][i]) dfs(i);
	}
}

int countSource() {
	memset(willReceive, 0, sizeof(willReceive));
	memset(canReceive, 0, sizeof(canReceive));

	while (true) {
		int i;
		for (i = 1; i <= n; i++) {
			if (!canReceive[i]) break;
		}
		if (i == n+1) break;
		
		memset(visited, 0, sizeof(visited));
		dfs(i);
		willReceive[i] = 1;
	}
	int total = 0;
	for (int i = 1; i <= n; i++) {
		if (willReceive[i]) total++;
	}
	return total;
}

void dfs2(int start) {
	if (visited[start]) return;
	visited[start] = true;
	for (int i = 1; i <= n; i++) {
		if (network[start][i]) dfs2(i);
	}
}

bool connected() {
	for (int i = 1; i <= n; i++) {
		memset(visited, 0, sizeof(visited));
		dfs2(i);

		for (int j = 1; j <= n; j++) {
			if (!visited[j]) return false;
		}
	}
	return true;
}

int main() {
	ifstream cin ("schlnet.in");
	ofstream cout ("schlnet.out");

	 cin >> n;
	for (int i = 1; i <= n; i++) {
		int j; cin >> j;
		while (j != 0) {
			network[i][j] = 1;

			cin >> j;
		}
	}

	sizeA = countSource();
	
	//reverse dfs
	for (int i = 1; i <= n; i++) {
		for (int j = i+1; j <= n; j++) {
			bool temp = network[i][j];
			network[i][j] = network[j][i];
			network[j][i] = temp;
		}
	}
	
	sizeB = countSource();
	int ans = 0;
	ans = max(sizeB, sizeA);

	if (connected()) ans = 0;

	cout << sizeA << "\n" << ans << endl;
	return 0;
}