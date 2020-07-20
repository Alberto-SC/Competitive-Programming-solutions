// Solution to: Bonsai
// By: Mees de Vries
//
// Expected answer: ACCEPTED
// Uses recursion on Catalan numbers

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

#define PRIME 1000000007

int main() {
    long long h, w, a; cin >> h >> w;

    // Taking height 1 as a special case, to avoid problems with h-2 later.
    if(h == 1) {
        cout << (w==1?1:0) << endl;
        return 0;
    }

    // We look at forests instead of trees. It's easier.
    h--;
    w--;

    // C[w, h] contains the number of balanced strings of parentheses 
    // of length 2w with depth at most h. (Original version of the problem.)
    vector<vector<long long>> C(w+1, vector<long long>(h+1, 0));

    // Boundary values.
    for(int i = 1; i <= w; i++) {
        C[i][0] = 0;
    }
    for(int i = 0; i <= h; i++) {
        C[0][i] = 1;
    }

    // Now fill the array using the recursion
    //
    //     C[w+1,h] = sum_{i=0}^n C[i,h-1]*C[w-i,h]
    for(int i = 1; i <= w; i++) {
        for(int j = 1; j <= h; j++) {
            // Filling C[i, j];
            for(int k = 0; k < i; k++) {
                a = (C[k][j-1] * C[i-1-k][j]) % PRIME;
                C[i][j] = (C[i][j] + a) % PRIME;
            }
        }
    }
    // We are looking for the number of such strings with depth *exactly* d,
    // so we return C[w,h] - C[w,h-1].
    cout << (C[w][h] - C[w][h-1]) % PRIME << endl;
    return 0;
}
