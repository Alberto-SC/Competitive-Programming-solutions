#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> h(n);
	for (int i = 0; i < n; i++) cin >> h[i];
	
	vector<int> uh = h;
	sort(begin(uh),end(uh));
	uh.erase(unique(begin(uh),end(uh)),end(uh));
	
	map<int,int> succ;
	for (int i = 0; i+1 < uh.size(); i++) succ[uh[i]] = uh[i+1];
	
	unordered_map<int, bool> done;

	int cuts = n-1;
	for (int i = 0; i+1 < n; i++) {
		if (h[i] == h[i+1]) cuts--;
		if (h[i+1] == succ[h[i]] && !done[h[i]]) {
			done[h[i]] = true;
			cuts--;
		}
	}
	cout << cuts << endl;
}
