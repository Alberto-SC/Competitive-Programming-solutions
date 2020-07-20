#include <iostream>
#include <list>
#include <string>

using namespace std;
list<int> l, r;
string input;

int main() {
	cin >> input;
	int n = input.length();
	for (int i = 0; i < n; i++) if (input[i] == '0') r.push_back(i);
	for (int i = 0; i < n; i++) {
		if (r.size() > 0 && r.front() <= i) {
			l.push_back(r.front());
			r.pop_front();
		}
		if (input[i] == '2') {
			if (l.size() == 0 || l.front() != -1) l.push_front(-1);
			if (r.size() == 0 || r.back() != n) r.push_back(n);
			int lPos = l.back(), rPos = r.front(), delta = lPos - i + rPos - i;
			if (lPos >= 0) input[lPos] = '1';
			if (rPos < n) input[rPos]++;
			l.pop_back();
			r.pop_front();
			input[i]--;
			input[i+delta]--;
			if (input[i+delta] == '0') {
				if (delta <= 0) l.push_back(i+delta);
				else r.push_front(i+delta);
			}
		}
	}

	cout << input;
	return 0;
}
