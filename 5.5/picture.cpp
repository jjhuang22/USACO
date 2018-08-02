/*
ID: jonatha61
PROG: picture
LANG: C++11
*/

//scan-line algorithm

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

#define f first
#define s second

struct rect{
	int x1, y1, x2, y2; 
};

int ans;
vector<rect> rects;
map<int, int> curLine;

void scanline() {
	vector<pair<int, int> > toScan[20001];
	for (auto a : rects) {
		toScan[a.y1 + 10000].push_back(make_pair(a.x1, 1));
		toScan[a.y1 + 10000].push_back(make_pair(a.x2, -1));
		toScan[a.y2 + 10000].push_back(make_pair(a.x1, -1));
		toScan[a.y2 + 10000].push_back(make_pair(a.x2, 1));
	}

	for (int i = 0; i < 20001; i++) {
		for (pair<int, int> a : toScan[i]) {
			curLine[a.f] += a.s;
			if (curLine[a.f] == 0) curLine.erase(a.f);
		}
		int x = 0;
		for (pair<int, int> a : curLine) {
			int xtemp = x + a.s;
			if (x == 0 || xtemp == 0) ans++;
			x = xtemp;
		}
	}
}

int main() {
	ifstream cin ("picture.in");
	ofstream cout ("picture.out");

	int n; cin >> n; rects.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
	}
	scanline();

	for (int i = 0; i < n; i++) {
		swap(rects[i].x1, rects[i].y1);
		swap(rects[i].x2, rects[i].y2);
	}
	scanline();

	cout << ans << endl;
	return 0;
}