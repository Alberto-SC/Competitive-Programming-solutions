#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<string> s(n);
	for (int i = 0; i < n; i++) cin >> s[i];
	int m; cin >> m;
	map<string,vector<pair<string,bool>>> dict;
	while (m--) {
		string d, e, c; cin >> d >> e >> c;
		dict[d].emplace_back(e,c == "correct");
	}

	long long correct_count = 1, total_count = 1;
	
	for (int i = 0; i < n; i++) {
		auto &translations = dict[s[i]];
		s[i] = translations[0].first;
		int cur_correct_count = 0;
		for (auto p: translations) cur_correct_count += p.second;
		
		correct_count *= cur_correct_count;
		total_count *= translations.size();
	}
	
	if (total_count == 1) {
		for (int i = 0; i < n; i++) {
			if (i > 0) cout << " ";
			cout << s[i];
		}
		cout << endl;
		cout << (correct_count ? "correct" : "incorrect") << endl;
	} else {
		cout << correct_count << " correct" << endl;
		cout << (total_count-correct_count) << " incorrect" << endl;
	}
}
