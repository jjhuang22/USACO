/*
ID: jonatha61
PROG: job
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

int main() {
	ifstream cin ("job.in");
	ofstream cout ("job.out");
	int n, m1, m2;
	cin >> n >> m1 >> m2;

	vector<int> a(m1, 0), b(m2, 0);
	
	for (int i = 0; i < m1; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < m2; i++) {
		cin >> b[i];
	}

	//arrays to hold when job i is finished for part A and part B
	vector<int> jobATime(n, 0), jobBTime(n, 0);

	//solve for part A
	vector<int> endATime(m1, 0);
	for (int i = 0; i < n; i++) {
		int minTime = INT_MAX, index = -1;
		for (int j = 0; j < m1; j++) {
			if (endATime[j] + a[j] < minTime) {
				minTime = endATime[j] + a[j];
				index = j;
			}
		}
		endATime[index] = minTime;
		jobATime[i] = minTime;
		if (i == n-1) cout << endATime[index] << " ";
	} 
	
	//solve for part B
	vector<int> endBTime(m2, 0);
	for (int i = n-1; i >= 0; i--) {
		int minTime = INT_MAX, index = -1;
		for (int j = 0; j < m2; j++) {
			if (endBTime[j] + b[j] < minTime) {
				minTime = endBTime[j] + b[j];
				index = j;
			}
		}
		endBTime[index] = minTime;
		jobBTime[i] = minTime;
	}

	int totalTime = 0;

	for (int i = 0; i < n; i++) {
		if (jobATime[i] + jobBTime[i] > totalTime) {
			totalTime = jobATime[i] + jobBTime[i];
		}
	}

	cout << totalTime << endl;
	
	return 0;
}