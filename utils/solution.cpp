#include "bits/stdc++.h"
using namespace std ;
 
void sol( ){
  int lo = 1, hi = 1000000, ans = -1 ;
  char op ;
  while( lo <= hi ){
    int mid = lo + hi >> 1 ;
    cout << 1 << " " << mid << endl ;
    cin >> op ;
    if( op == -1 ){
      return ;
    }
    if( op == '<' ){
      ans = mid ;
      lo = mid+1 ;
    }
    else{
      hi = mid-1 ;
    }
  }
  cout << 0 << " " << ans << endl ;
}
 
signed main( ){
  sol();
}