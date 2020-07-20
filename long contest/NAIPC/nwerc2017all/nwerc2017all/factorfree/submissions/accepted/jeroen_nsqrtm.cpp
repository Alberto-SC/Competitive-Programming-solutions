#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>

#define MAXN 1000000

using namespace std;

set<int> primeFactors(int n) {
  set<int> ret;

  for(int i = 2; i * i <= n; i += (i == 2 ? 1 : 2)) {
    if(n % i == 0) {
      ret.insert(i);
      while(n % i == 0)
	n /= i;
    }
  }
  if(n > 1) ret.insert(n);
  return ret;
}

set<int> factors[MAXN];
int res[MAXN];
int conf_l[MAXN];
int conf_r[MAXN];
bool possible;

void fill(int from, int to, int parent) {
  if(from > to) {
    return;
  } else if(from == to) {
    res[from] = parent;
  } else {
    for(int i = 0; i < (to - from + 2) / 2; i++) {
      if(conf_l[from+i] < from && conf_r[from+i] > to) {
	res[from+i] = parent;
	fill(from, from+i-1, from+i+1);
	fill(from+i+1,to,from+i+1);
	return;
      }
      
      if(conf_l[to-i] < from && conf_r[to-i] > to) {
	res[to-i] = parent;
	fill(from, to-i-1, to-i+1);
	fill(to-i+1,to,to-i+1);
	return;
      }
    }
    
    possible = false;
  }
}

int a[MAXN];

int main() {
  int n;
  scanf("%d\n", &n);
  for(int i = 0; i < n; i++)
    scanf("%d", &a[i]);

  for(int i = 0; i < n; i++)
    factors[i] = primeFactors(a[i]);

  map<int, int> last;
  for(int i = 0; i < n; i++) {
    conf_l[i] = -1;
    for(set<int>::iterator f = factors[i].begin(); f != factors[i].end(); f++) {
      if(last.find(*f) != last.end()) {
	conf_l[i] = max(conf_l[i], last[*f]);
      }
      last[*f] = i;
    }
  }

  last.clear();
  for(int i = n - 1; i >= 0; i--) {
    conf_r[i] = n;
    for(set<int>::iterator f = factors[i].begin(); f != factors[i].end(); f++) {
      if(last.find(*f) != last.end()) {
	conf_r[i] = min(conf_r[i], last[*f]);
      }
      last[*f] = i;
    }
  }

  possible = true;
  fill(0, n - 1, 0);

  if(!possible) {
    printf("impossible\n");
  } else {
    for(int i = 0; i < n; i++) {
      if(i > 0) printf(" ");
      printf("%d", res[i]);
    }
    printf("\n");
  }
  
  return 0;
}
