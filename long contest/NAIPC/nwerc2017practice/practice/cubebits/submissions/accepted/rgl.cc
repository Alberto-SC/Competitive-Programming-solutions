#include <algorithm>
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

int main(){
  int n; cin>>n; while (n--){
    uint32_t x; cin>>x; string s; do s+=('0'+(x%3)), x/=3; while (x);
    reverse(s.begin(),s.end());
    cout<<s<<endl;
  }
}
