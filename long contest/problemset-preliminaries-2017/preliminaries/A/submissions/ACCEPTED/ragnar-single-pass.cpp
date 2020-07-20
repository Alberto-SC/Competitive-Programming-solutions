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
	int cur = 0;
	string prev;
	bool ambiguous = false;
	for(int i = 0; i < l; ++i) {
		string s;
		cin >> s;
		int last = cur;
		while(cur < n && gs[cur].find(s) == gs[cur].end()) ++cur;
		if(cur == n) return cout << "impossible\n", 0;
		if(i > 0 && !ambiguous) {
			while(++last <= cur)
				if(gs[last].find(prev) != gs[last].end()) ambiguous = true;
		}
		prev = move(s);
	}
	while(++cur < n && !ambiguous)
		if(gs[cur].find(prev) != gs[cur].end()) ambiguous = true;
	return cout << (ambiguous ? "ambiguous\n" : "unique\n"), 0;
}
