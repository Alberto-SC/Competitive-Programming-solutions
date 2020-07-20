#include <iostream>
#include <string>
using namespace std ;
typedef long long ll ;
// slow version.
int main() {
   string s, t ;
   cin >> s >> t ;
   ll r = 0 ;
   for (int i=0; i<=s.size(); i++) {
      int k = 0 ;
      int j = i ;
      for (; k < t.size() && j < s.size(); j++) {
         if (t[k] == s[j])
            k++ ;
      }
      if (k >= t.size())
         r += s.size() - j + 1 ;
   }
   cout << r << endl ;
}
