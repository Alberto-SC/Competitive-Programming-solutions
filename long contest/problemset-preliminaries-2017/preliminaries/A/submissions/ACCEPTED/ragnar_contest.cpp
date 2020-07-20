#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
int main() {
	int n, k;
	cin >> n >> k;
	vector<set<string>> gs(n);
	while(k--) {
		int i;
		string s;
		cin >> i >> s;
		gs[i].insert(s);
	}
	int l;
	cin >> l;
	vector<string> v(l);
	for(auto &s : v) cin >> s;
	vector<int> min, max;
	{
		auto it = v.begin();
		for(int i = 0; i < n; ++i)
			while(it != v.end() && gs[i].find(*it) != gs[i].end()) min.push_back(i), ++it;
		if(it != v.end()) return cout << "impossible\n", 0;
	}
	{
		auto it = v.rbegin();
		for(int i = n - 1; i >= 0; --i)
			while(it != v.rend() && gs[i].find(*it) != gs[i].end()) max.push_back(i), ++it;
	}
	reverse(max.begin(), max.end());
	cout << (min == max ? "unique\n" : "ambiguous\n");
	return 0;
}
