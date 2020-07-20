#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> r(N);
  for (int i=0; i<N; i++)
    cin >> r[i];
  sort(r.begin()+1, r.end());

  int byes=0;
  while ((N+byes) & (N+byes-1)) {
    byes++;
  }
  vector<int> s;
  for (int i=0; i<N; i++) {
    s.push_back(r[i]);
    if (i<byes) s.push_back(0);
  }
  r = s;

  N = s.size();
  vector<map<int,double>> prob(N);
  for (int i=0; i<N; i++)
    prob[i][i] = 1.0;

  while (prob.size() > 1) {
      vector<map<int,double>> next(prob.size()/2);
      for (int i=0; i<prob.size(); i+=2) {
      for (auto x : prob[i]) {
	for (auto y : prob[i+1]) {
	  int rx = r[x.first];
	  double px = x.second;
	  int ry = r[y.first];
	  double py = y.second;
	  next[i/2][x.first] += px * py * (rx+ry==0 ? 0.5 : 1.0 * rx / (rx + ry));
	  next[i/2][y.first] += px * py * (rx+ry==0 ? 0.5 : 1.0 * ry / (rx + ry));
	}
      } 
    }
    prob = next;
  }
  cout << setprecision(10) << prob[0][0] << endl;
  return 0;
}
