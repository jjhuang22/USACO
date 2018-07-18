/*
ID: jonatha61
PROG: lgame
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

const int points[] = {
	2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7
};

vector<string> dict;
vector<pair<string, string> > ans;
int maxScore;

int calculate(string a, string b) {
	int sum = 0;
	for (int i = 0; i < a.length(); i++) sum += points[a[i] - 'a'];
	for (int i = 0; i < b.length(); i++) sum += points[b[i] - 'a'];
	return sum;
}

void collectPairs(string a, string b) {
	if (binary_search(dict.begin(), dict.end(), a) && binary_search(dict.begin(), dict.end(), b)) {
		int sum = calculate(a, b);
		if (sum >= maxScore) {

			if (a.compare("") == 0) swap(a, b);
			else if (a > b && b.compare("") != 0) swap(a, b);

			if (sum > maxScore) {
				ans.clear();
				maxScore = sum;
			}
			ans.push_back(make_pair(a, b));
		}
	}
}

int main() {
	ifstream fin ("lgame.dict");
	string word; fin >> word;
	while (word != ".") {
		dict.push_back(word);
		fin >> word;
	}
	dict.push_back("");
	sort(dict.begin(), dict.end());

	ifstream cin ("lgame.in");
	ofstream cout ("lgame.out");

	string s; cin >> s;
	sort(s.begin(), s.end());

	do {
		for (int i = 3; i <= s.length(); i++) {
			//one word 
			collectPairs(s.substr(0, i), "");

			//two words
			for (int j = 3; i+j <= s.length(); j++) {
				collectPairs(s.substr(0, i), s.substr(i, j));
			}
		}
	} while (next_permutation(s.begin(), s.end()));

	sort(ans.begin(), ans.end());

	set<pair<string, string> > finalSet(ans.begin(), ans.end());

	cout << maxScore << endl;
	for (auto f : finalSet) {
		cout << f.first;
		if (f.second.length() != 0) cout << " " << f.second;
		cout << "\n";
	}

	return 0;
}