#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	vector<size_t> z;

	int iterations = 0; // debugging
	
	for (size_t i = 0; i < s.length(); ++iterations) {
		if (s[i] < '2') {
			if (s[i] == '0') z.push_back(i);
			++i;
		} else {
			s[i] -= 1;
			if (i + 1 < s.length()) s[i + 1] += 1;
			if (!z.empty())
				s[z.back()]++,
				z.back()++;
			else
				z.push_back(0);
			s[z.back()]--;
			if (z.back() == i) z.pop_back();
		}
	}
	
	cerr << "Required " << iterations << " steps." << endl;
	cout << s << endl;

	return 0;
}
