#include <algorithm>
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

// Meet in the middle algorithm.

uint64_t solve(uint16_t v){
  uint64_t res=0;
  while (v--){
    ++res;
    for (uint64_t mask=1; mask<=res; mask*=10){
      uint64_t const digit=(res%(mask*10))/(mask);
      if (digit>=3){
        res+=mask*7;
      }
    }
  }
  return res;
}

int main(){
  int n; cin>>n; while (n--){
    uint32_t x; cin>>x;
    unsigned long long a=solve(x/59049);
    unsigned long long b=solve(x%59049);
    if (a) printf("%llu%010llu\n", a, b);
    else printf("%llu\n", b);
  }
}
