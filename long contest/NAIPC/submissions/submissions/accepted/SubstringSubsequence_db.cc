// Problem         : Substring Subsequence (NAIPC 2019)
// Author          : Darcy Best
// Expected Result : AC
// Complexity      : O(|s| * |t| + |s| * ALPHABET)

// For each location in s and each letter, store the next location of that letter.
// For each left endpoint, determine the closest right endpoint greedily.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
  string s, t; cin >> s >> t;

  int n = s.length(), m = t.length();

  vector<vector<int> > next(n+2, vector<int>(26, n));

  for(int i=n-1;i>=0;i--){
    for(int j=0;j<26;j++)
      next[i][j] = next[i+1][j];
    next[i][s[i]-'a'] = i;
  }

  long long ans = 0;
  for(int L=0;L<n;L++){
    int R=L;
    for(int idx=0;idx<m;R=next[R][t[idx++]-'a']+1) ;
    ans += (n+1)-R;
  }
  
  cout << ans << endl;
}
