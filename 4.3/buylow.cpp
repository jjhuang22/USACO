/*
ID: jonatha61
PROG: buylow
LANG: C++11
*/

// dp holds the length of LDS starting at index i

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int prices[5000], dp[5000], lis;
vector<int> numLIS[5000];
vector<int> finalLIS;

// addition for bignum
vector<int> add(vector<int> x, vector<int> y) {
	while (x.size() < y.size()) x.push_back(0);
	while (x.size() > y.size()) y.push_back(0);
	int carry = 0;
	vector<int> ans(x.size());
	for (int i = 0; i < ans.size(); i++) {
		ans[i] = x[i] + y[i] + carry;
		carry = ans[i]/10;
		ans[i] %= 10;
	}
	if (carry != 0) ans.push_back(carry);
	return ans;
}

int main() {
	ifstream cin ("buylow.in");
	ofstream cout ("buylow.out");
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> prices[i];
		dp[i] = 1;
	}

	for (int i = n-1; i >= 0; i--) {
		for (int j = i+1; j < n; j++) {
			if (prices[j] < prices[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		lis = max(lis, dp[i]);
	}

	for (int i = n-1; i >= 0; i--) {
		set<int> usedPrices;
		numLIS[i].push_back(0);
		for (int j = i + 1; j < n; j++) {
			if (prices[j] < prices[i] && (dp[i] == dp[j] + 1) && usedPrices.find(prices[j]) == usedPrices.end()) {
				usedPrices.insert(prices[j]);
				numLIS[i] = add(numLIS[i], numLIS[j]);
			}
		}

		if (numLIS[i].size() == 1 && numLIS[i][0] == 0) numLIS[i].assign(1, 1);
	}

	set<int> s;
	finalLIS.push_back(0);
	for (int i = 0; i < n; i++) {
		if (dp[i] == lis && s.find(prices[i]) == s.end()) {
			s.insert(prices[i]);
			finalLIS = add(finalLIS, numLIS[i]);
		}
	}

	cout << lis << " ";
	for (int i = finalLIS.size() - 1; i >= 0; i--) {
		cout << finalLIS[i];
	}
	cout << "\n";
}

// int num[5001], dp[5000];
// int n;
// vector<int> lis[5000];
// vector<int> finAns;

// // addition for bignum
// vector<int> add(vector<int> x, vector<int> y) {
// 	while (x.size() < y.size()) x.push_back(0);
// 	while (x.size() > y.size()) y.push_back(0);
// 	int carry = 0;
// 	vector<int> ans(x.size());
// 	for (int i = 0; i < ans.size(); i++) {
// 		ans[i] = x[i] + y[i] + carry;
// 		carry = ans[i]/10;
// 		ans[i] %= 10;
// 	}
// 	if (carry != 0) ans.push_back(carry);
// 	return ans;
// }


// int main() {
// 	ifstream cin ("buylow.in");
// 	ofstream fout ("buylow.out");
// 	cin >> n;
// 	for (int i = 0; i < n; i++) {
// 		cin >> num[i];
// 		dp[i] = 1;
// 	}
// 	for (int i = 0; i < n+1; i++) {
// 		for (int j = 0; j < i; j++) {
// 			if (num[j] > num[i]) {
// 				dp[i] = max(dp[i], dp[j] + 1);
// 			}
// 		}

// 		if (dp[i] == 1) lis[i].push_back(1);
// 		else {
// 			set<int> s;
// 			for (int j = i-1; j >= 0; j--) {
// 				if (dp[j] + 1 == dp[i] && num[j] > num[i] && s.find(num[j]) == s.end()) {
// 					s.insert(num[j]);
// 					lis[i] = add(lis[j], lis[i]);
// 				}
// 			}
// 		}
// 	}

// 	fout << dp[n] - 1 << " ";
// 	for (int i = lis[n].size() - 1; i >= 0; i--) {
// 		fout << lis[n][i];
// 	}
// 	fout << "\n";
// 	return 0;
// }