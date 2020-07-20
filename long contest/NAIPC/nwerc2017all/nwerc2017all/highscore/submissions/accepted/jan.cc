#include <iostream>

using namespace std;

int main() {
  int runs;
  cin >> runs;
  while (runs-- > 0) {
    long long a,b,c,d;
    cin >> a >> b >> c >> d;
    if (a>c) swap(a,c);
    if (b>c) swap(b,c);
    long long score = 0;
    for (int da=0; da<10 && da<=d; da++)
      for (int db=0; db<10 && da+db<=d; db++) {
	int dc = d-da-db;
	score = max(score, (a+da)*(a+da) + (b+db)*(b+db) + (c+dc)*(c+dc)
		    + 7 * min(a+da, min(b+db,c+dc)));
      }
    cout << score << endl;
  }
  return 0;
}
