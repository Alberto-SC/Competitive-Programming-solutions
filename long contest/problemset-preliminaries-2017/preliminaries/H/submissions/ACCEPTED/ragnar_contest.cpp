#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	array<vector<int>, 2> vs;
	for(auto &v : vs) {
		int k;
		cin >> k;
		v.resize(k);
		for(auto &x : v) cin >> x;
		sort(v.begin(), v.end());
	}
	int ans = 0, last = 3, i = 0, j = 0;
	while(i < vs[0].size() && j < vs[1].size()) {
		if(vs[0][i] == vs[1][j]) {
			++ans;
			last = 3;
			++i, ++j;
		} else if(vs[0][i] < vs[1][j]) {
			if(last & 2) {
				++ans;
				last = 1;
			}
			++i;
		} else {
			if(last & 1) {
				++ans;
				last = 2;
			}
			++j;
		}
	}
	if(i < vs[0].size() && (last & 2)) ++ans;
	if(j < vs[1].size() && (last & 1)) ++ans;
	cout << ans << endl;
	return 0;
}
