#include <bits/stdc++.h>
using namespace std;

int main() {
	string a; cin >> a;
	int n = a.size();

	set<int> p[3];
	for (int i = 0; i < n; i++) p[a[i]-'0'].insert(i);

	while (p[2].size()) {
		p[0].insert(-1), p[0].insert(n);
		
		int i = *begin(p[2]);
		p[2].erase(begin(p[2]));

		int j = *prev(p[0].lower_bound(i));
		int k = *p[0].lower_bound(i);

		p[0].erase(j), p[0].erase(k);
		p[0].insert(j+k-i);
	}
	
	for (int i = 0; i < n; i++) cout << !p[0].count(i);
	cout << endl;
}
