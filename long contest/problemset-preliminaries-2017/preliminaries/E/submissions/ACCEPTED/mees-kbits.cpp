#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <climits>

using namespace std;

int main() {
    long long N, k; cin >> N >> k;
    N++;
    int ct = 0;
    for(long long i = 0; i < 60; i++) {
        if(N & (1LL << i)) {
            ct++;
        }
    }
    if(ct > k) {
        long long j = 0;
        while(ct >= k || N & (1LL << j)) {
            if(N & (1LL << j)) {
                ct--;
                N &= ~(1LL << j);
            }
            j++;
        }
        N |= (1LL << j);
        ct++;
    }
    if(ct < k) {
        long long j = 0;
        while(ct < k) {
            if(!(N & (1LL << j))) {
                N |= (1LL << j);
                ct++;
            }
            j++;
        }
    }
    cout << N << endl;
    return 0;
}
