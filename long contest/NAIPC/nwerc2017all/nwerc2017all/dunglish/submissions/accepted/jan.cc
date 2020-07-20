#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
 
  map<string,int> correct, incorrect;
  map<string,string> translation;

  int n;
  cin >> n;
  vector<string> sentence(n);
  for (int i=0; i<n; i++)
    cin >> sentence[i];

  int m;
  cin >> m;
  for (int i=0; i<m; i++) {
    string w,t,c;
    cin >> w >> t >> c;
    translation[w] = t;
    if (c == "correct") {
      correct[w]++;
    } else {
      incorrect[w]++;
    }
  }

  long long num_correct = 1;
  long long num_translation = 1;
  
  for (string w : sentence) {
    num_correct *= correct[w];
    num_translation *= correct[w] + incorrect[w];
  }

  if (num_translation == 1) {
    bool first = true;
    for (string w : sentence) {
      if (first)
	first = false;
      else
	cout << " ";
      cout << translation[w];
    }
    cout << endl;
    if (num_correct == 1)
      cout << "correct" << endl;
    else
      cout << "incorrect" << endl;
  } else {
    cout << num_correct << " correct" << endl;
    cout << num_translation - num_correct << " incorrect" << endl;
  }
  return 0;
}
