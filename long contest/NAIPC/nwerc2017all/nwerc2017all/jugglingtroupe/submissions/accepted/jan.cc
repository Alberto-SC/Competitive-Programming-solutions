#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  string s;
  cin >> s;
  vector<set<int>> pos(3);
  for (int i=0; i<s.size(); i++)
    pos[s[i]-'0'].insert(i);
  pos[0].insert(-1);
  pos[0].insert(s.size());
  while (!pos[2].empty()) {
    int pos2 = *pos[2].begin();
    auto it = pos[0].lower_bound(pos2);
    int right0 = *it;
    int left0 = *--it;
    pos[2].erase(pos2);
    pos[1].insert(pos2);
    s[pos2]='1';
    int x = left0+right0-pos2;
    int n = s[x]-'0';
    pos[n].erase(x);
    pos[n-1].insert(x);
    s[x]--;
    if (left0 >= 0) {
      pos[0].erase(left0);
      pos[1].insert(left0);
      s[left0]='1';
    }
    if (right0 < s.size()) {
      pos[0].erase(right0);
      pos[1].insert(right0);
      s[right0]='1';
    }
  }
  cout << s << endl;
  return 0;
}
