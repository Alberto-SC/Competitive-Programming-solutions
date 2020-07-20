#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
int main() {
   string s, t ;
   cin >> s >> t ;
   vector<ll> cnts(t.size()+1) ;
   ll r = 0 ;
   for (int i=0; i<=s.size(); i++) {
      r += cnts[t.size()] ;
      if (i == s.size())
         break ;
      cnts[0]++ ;
      for (int j=t.size()-1; j>=0; j--) {
         if (s[i] == t[j]) {
            cnts[j+1] += cnts[j] ;
            cnts[j] = 0 ;
         }
      }
   }
   cout << r << endl ;
}
