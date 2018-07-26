/*
ID: jonatha61
PROG: tour
LANG: C++11
*/

//DP black magic 

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

map<string, int> cityNum;
bool flights[101][101];
int dp[101][101];

int main() {
	ifstream cin ("tour.in");
	ofstream cout ("tour.out");

	int n, v; cin >> n >> v;
	string city1, city2;
	for (int i = 0; i < n; i++) {
		cin >> city1;
		cityNum[city1] = i;
	}


	for (int i = 0; i < v; i++) {
		cin >> city1 >> city2;
		int a = cityNum[city1];
		int b = cityNum[city2];
		flights[a][b] = flights[b][a] = true;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = -1;
		}
	}
	dp[0][0] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = 0; k < j; k++) {
				if (dp[i][k] > 0 && flights[k][j] && dp[i][k] + 1 > dp[i][j]) {
					dp[i][j] = dp[j][i] = dp[i][k] + 1;
				}
			}
		}
	}

	int ans = 1;
	for (int i = 0; i < n; i++) {
		if (dp[i][n-1] > ans && flights[i][n-1]) {
			ans = dp[i][n-1];
		}
	}
	
	cout << ans << endl;
	return 0;
}