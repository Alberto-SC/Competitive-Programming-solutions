//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef pair<string, bool> psb;
typedef long long ll;
int main() {
  int n; cin >> n;
  vector<string> s(n);
  rep(i,0,n) cin >> s[i];

  int m; cin >> m;
  unordered_map<string, vector<psb>> translations;
  rep(i,0,m) {
    string w, t, c;
    cin >> w >> t >> c;
    translations[w].emplace_back(t, c == "correct");
  }

  vector<ll> comb = {0, 1};
  rep(i,0,n) {
    const string& cur = s[i];
    vector<ll> n_comb(2, 0);
    for (const auto& transl : translations[cur]) {
      n_comb[transl.second] += comb[1];
      n_comb[0] += comb[0];
    }
    swap(comb, n_comb);
  }

  if (comb[0] + comb[1] != 1) {
    printf("%lld correct\n", comb[1]);
    printf("%lld incorrect\n", comb[0]);
  } else {
    bool correct = true;
    rep(i,0,n) {
      printf("%s", translations[s[i]][0].first.c_str());
      correct &= translations[s[i]][0].second;
      if (i + 1 < n) printf(" ");
      else printf("\n");
    }
    printf("%s\n", correct ? "correct" : "incorrect");
  }
}
