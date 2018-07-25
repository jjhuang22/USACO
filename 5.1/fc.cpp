/*
ID: jonatha61
PROG: fc
LANG: C++11
*/

// gift-wrapping algorithm, choose bottommost point on convex hull as initial point
// note the while loop in the for loop 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits.h>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

#define f first
#define s second 

vector<pair<double, double> > points;
vector<pair<double, double> > hull;
double startX, startY, ans;

double dist(pair<double, double> a, pair<double, double> b) {
	return sqrt((b.f-a.f)*(b.f-a.f) + (b.s-a.s)*(b.s-a.s));
}

bool comp(pair<double, double> a, pair<double, double> b) {
	double a1 = atan((a.second-startY)/(a.first-startX));
	double b1 = atan((b.second-startY)/(b.first-startX));
	if (a1 < 0) a1 += 4*atan(1);
	if (b1 < 0) b1 += 4*atan(1);
	if (a1 == b1) return (dist(a, make_pair(startX, startY)) < dist(b, make_pair(startX, startY)));
	else return (a1 < b1);
}

//look at z component of cross product between (b-a) x (c-a)
double crossprod(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
	return (b.f-a.f)*(c.s-a.s) - (b.s-a.s)*(c.f-a.f);
}

int main() {
	ifstream cin ("fc.in");
	ofstream cout ("fc.out");

	int n; cin >> n;
	double x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points.push_back(make_pair(x, y));
	}

	//find bottom-left point on convex hull as starting point
	for (int i = 1; i < n; i++) {
		if (points[i].second < points[0].second || (points[i].second == points[0].second && points[i].first < points[0].first)) {
			swap(points[i], points[0]);
		}
	}

	startX = points[0].f, startY = points[0].s;

	sort(points.begin()+1, points.end(), comp);

	hull.push_back(points[0]), hull.push_back(points[1]);
	int curr = 1;
	for (int i = 2; i < n; i++) {
		while (crossprod(hull[curr-1], hull[curr], points[i]) <= 0) {
			hull.erase(hull.begin() + curr);
			curr--;

		}
		curr++;
		hull.push_back(points[i]);
	}


	for (int i = 0; i < hull.size()-1; i++) {
		ans += dist(hull[i+1], hull[i]);
	}
	ans += dist(hull[hull.size()-1], hull[0]);

	cout << setprecision(2) << fixed << ans << endl;
	return 0;
}