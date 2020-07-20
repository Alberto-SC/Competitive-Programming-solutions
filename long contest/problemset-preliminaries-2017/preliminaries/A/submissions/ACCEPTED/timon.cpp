#include <bits/stdc++.h>
using namespace std;

vector<size_t> seq(vector<unordered_set<string>> &p, vector<string> &r) {
	vector<size_t> a;
	for (size_t i = 0, j = 0; i < p.size(); ++i)
		while (j < r.size() && p[i].count(r[j])) a.push_back(i), ++j;
	if (a.size() < r.size()) a.clear();
	return a;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k;
	cin >> n >> k;

	vector<unordered_set<string>> park(n);
	while (k--) {
		int i;
		string s;
		cin >> i >> s;
		park[i].insert(s);
	}

	int l;
	cin >> l;
	vector<string> route(l);
	for (string &s : route) cin >> s;

	vector<size_t> a1, a2;
	a1 = seq(park, route);
	if (a1.empty()) {
		cout << "impossible\n";
		return 0;
	}

	reverse(park.begin(), park.end());
	reverse(route.begin(), route.end());
	a2 = seq(park, route);
	reverse(a2.begin(), a2.end());
	
	bool unique = true;
	for (size_t i = 0; i < route.size(); ++i)
		unique = unique && (a1[i] + a2[i] + 1 == park.size());

	cout << (unique ? "unique\n" : "ambiguous\n");
}
