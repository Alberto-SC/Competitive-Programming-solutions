#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>

using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> hs;
  set<int> h_set;
  int prev = -1;
  for (int i=0; i<N; i++) {
    int h;
    cin >> h;
    if (h != prev) {
      hs.push_back(h);
      h_set.insert(h);
    }
    prev = h;
  }
  N = hs.size();

  map<int,int> idx,cnt;
  int H=0;
  for (int h : h_set)
    idx[h] = H++;
  for (int& h : hs) {
    h = idx[h];
    cnt[h]++;
  }
  int cuts = N - 1;
  vector<set<int>> pos(H);
  for (int i=0; i+1<N; i++) {
    if (hs[i]+1 == hs[i+1]) pos[hs[i]].insert(i);
  }
  set<int> onepos;
  for (int h=0; h<H; h++)
    if (pos[h].size() == 1)
      onepos.insert(h);

  while (!onepos.empty()) {
    int h = *onepos.begin();
    onepos.erase(h);
    if (pos[h].empty())
      continue;
    int i = *pos[h].begin();
    pos[h].erase(i);
    cuts--;
    if (i>0 && cnt[h]>1 && hs[i-1]+1==h) {
      pos[h-1].erase(i-1);
      if (pos[h-1].size() == 1)
	onepos.insert(h-1);
    }
    if (i+2<N && cnt[h+1]>1 && h+2==hs[i+2]) {
      pos[h+1].erase(i+1);
      if (pos[h+1].size() == 1)
	onepos.insert(h+1);
    }    
  }

  for (int h=0; h<H; h++)
    if (!pos[h].empty()) {
      cuts--;
    }

  cout << cuts << endl;
  return 0;
}
