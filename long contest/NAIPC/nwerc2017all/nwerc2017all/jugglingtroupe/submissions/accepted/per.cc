#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

void add(set<pii> &ones, pii ival) {
    auto it = ones.lower_bound(ival);
    assert(it == ones.end() || it->first > ival.second);
    if (it != ones.end() && it->first == ival.second+1) {
        ival.second = it->second;
        ones.erase(it++);
    }
    if (it != ones.begin() && (--it)->second == ival.first-1) {
        ival.first = it->first;
        ones.erase(it);
    }
    ones.insert(ival);
}

int main(void) {
    int n;
    string s;
    cin >> s;
    n = s.length();
    vector<int> twos;
    set<pii> ones;
    for (int i = 0; i < n; ++i)
        if (s[i] == '2') twos.push_back(i);
    for (int i = 0, j; i < n; ++i) {
        if (s[i] != '0') {
            for (j = i; j < n && s[j] != '0'; ++j);
            ones.insert(pii(i, j-1));
            i = j;
        }
    }
    for (int i: twos) {
        auto it = ones.lower_bound(pii(i, n+1));
        if (it == ones.begin() || (--it)->second < i) {
            add(ones, pii(i, i));
        } else {
            assert(it->first <= i && i <= it->second);
            pii n1 = pii(it->first - 1, it->first + it->second - i - 1);
            if (n1.first < 0) n1.first = 0;
            pii n2 = pii(it->first + it->second - i + 1, it->second + 1);
            if (n2.second >= n) n2.second = n-1;
            ones.erase(it);
            add(ones, n1);
            add(ones, n2);
        }
    }
    for (auto &c: s) c = '0';
    for (auto &r: ones)
        for (int i = r.first; i <= r.second; ++i)
            s[i] = '1';
    cout << s << endl;
}
