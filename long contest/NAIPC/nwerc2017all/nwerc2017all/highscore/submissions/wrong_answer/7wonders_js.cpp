#include <iostream>

using namespace std;

int main(){
  int n;
  cin >> n;
  for(int i = 0; i < n; ++i){
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    long long ans = 0;
    for(long long sm = min(a, min(b, c)), it = 1000000; it; sm++, it--){
      long long needs = max(sm - a, 0LL) + max(sm - b, 0LL) + max(sm - c, 0LL);
      if(needs > d) break;
      long long left = d - needs;

      long long na = max(a, sm), nb = max(b, sm), nc = max(c, sm);
      na += left;
      long long sc = 7 * min(na, min(nb, nc)) + na * na + nb * nb + nc * nc;
      ans = max(ans, sc);
    }
    cout << ans << endl;
  }
}
