/*
ID: jonatha61
PROG: window
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

struct rect {
	int x1, y1, x2, y2, id;
};	

map<char, int> identifier;
vector<rect> y;
vector<rect> x;

void addSmall(int a, int b, int c, int d, int id) {
	rect temp;
	temp.x1 = a;
	temp.y1 = b;
	temp.x2 = c;
	temp.y2 = d;
	temp.id = id;
	x.push_back(temp);
}

void perform(int a, int b, int c, int d, int id) {
	int i = 0, l = x.size();

	while (i < l) {
		int r1, r2, r3, r4;

		r1 = max(x[i].x1, a);
		r2 = min(x[i].x2, c);
		if (r1 >= r2) {
			i++;
			continue;
		}

		r3 = max(x[i].y1, b);
		r4 = min(x[i].y2, d);
		if (r3 >= r4) {
			i++;
			continue;
		}

		if (x[i].x1 < r1) addSmall(x[i].x1, x[i].y1, r1, x[i].y2, x[i].id);
		if (x[i].x2 > r2) addSmall(r2, x[i].y1, x[i].x2, x[i].y2, x[i].id);
		if (x[i].y1 < r3) addSmall(r1, x[i].y1, r2, r3, x[i].id);
		if (x[i].y2 > r4) addSmall(r1, r4, r2, x[i].y2, x[i].id);
		x.erase(x.begin() + i);
		l--;
	}

	addSmall(a, b, c, d, id);
}


int main() {
	ifstream cin ("window.in");
	ofstream cout ("window.out");

	for (int i = 0; i < 26; i++) {
		identifier[i+'A'] = i;
		identifier[i+'a'] = i + 26;
	}
	for (int i = 0; i < 10; i++) identifier[i+'0'] = i + 52;

	while(!cin.eof()) {
		char command, ident, temp;
		int a, b, c, d;

		cin >> command;
		if (!cin.eof()) {
			if (command == 'w') {
				cin >> temp >> ident >> temp >> a >> temp >> b >> temp >> c >> temp >> d >> temp;

				rect q;
				q.x1 = min(a, c);
				q.x2 = max(a, c);
				q.y1 = min(b, d);
				q.y2 = max(b, d);
				q.id = identifier[ident];

				y.push_back(q);
				perform(q.x1, q.y1, q.x2, q.y2, q.id);
			}
			else if (command == 't') {
				cin >> temp >> ident >> temp;
				for (int i = 0; i < y.size(); i++) {
					if (y[i].id == identifier[ident]) {
						rect top = y[i];
						for (int j = i; j < y.size() - 1; j++) {
							y[j] = y[j+1];
						}
						y[y.size() - 1] = top;
						break;
					}
				}
			}
			else if (command == 'b') {
				cin >> temp >> ident >> temp;
				for (int i = 0; i < y.size(); i++) {
					if (y[i].id == identifier[ident]) {
						rect bot = y[i];
						for (int j = i; j > 0; j--) {
							y[j] = y[j-1];
						}
						y[0] = bot;
						break;
					}
				}
			}
			else if (command == 'd') {
				cin >> temp >> ident >> temp;
				for (int i = 0; i < y.size(); i++) {
					if (y[i].id == identifier[ident]) {
						y.erase(y.begin() + i);
						break;
					}
				}
			}
			else if (command == 's') {
				cin >> temp >> ident >> temp;
				double area = 0;

				for (int i = 0; i < x.size(); i++) {
					if (x[i].id == identifier[ident]) {
						area += (x[i].x2 - x[i].x1) * (x[i].y2 - x[i].y1);
					}
				}

				for (int i = 0; i < y.size(); i++) {
					if (y[i].id == identifier[ident]) {
						area /= (y[i].x2 - y[i].x1) * (y[i].y2 - y[i].y1);
						break;
					}
				}

				cout << fixed << setprecision(3) << area * 100 << endl;
			}

			if (command == 't' || command == 'b' || command =='d') {
				x.clear();
				for (int i = 0; i < y.size(); i++) {
					perform(y[i].x1, y[i].y1, y[i].x2, y[i].y2, y[i].id);
				}
			}
		}

	}
	
	return 0;
}