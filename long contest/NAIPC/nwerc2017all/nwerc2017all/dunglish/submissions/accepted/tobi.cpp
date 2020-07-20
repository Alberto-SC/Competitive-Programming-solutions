#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
int n, m;
string s[20], c, d, e;
bool correct[100000];
multimap<string,pair<string,bool>> dict;
long long corrects = 1, totals = 1;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> s[i];
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> d >> e >> c;
		dict.insert(pair<string,pair<string,bool>>(d, pair<string,bool>(e, c[0] == 'c')));
	}
	for (int i = 0; i < n; i++) {
		auto same = dict.equal_range(s[i]);
		long long localCount = 0, localCorrects = 0;
		for (auto it = same.first; it != same.second; it++) {
			localCount++;
			localCorrects += (it->second.second);
		}
		totals *= localCount;
		corrects *= localCorrects;
	}
	if (totals == 1) {
		for (int i = 0; i < n; i++) cout << dict.find(s[i])->second.first << " ";
		cout << (corrects ? "correct" : "incorrect") << endl;
	} else {
		cout << corrects << " correct" << endl;
		cout << (totals - corrects) << " incorrect" << endl;
	}
	return 0;
}
