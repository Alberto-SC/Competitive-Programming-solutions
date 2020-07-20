#include <algorithm>
#include <iostream>
#include <vector>

/*
Forgets to sort input
*/

using namespace std;

int main () {
    int n1;
    cin >> n1;

    vector<int> preference1(n1);
    for(int i = 0; i < n1; ++i) {
        cin >> preference1[i];
    }

    // sort(preference1.begin(), preference1.end());

    int n2;
    cin >> n2;

    vector<int> preference2(n2);
    for(int i = 0; i < n2; ++i) {
        cin >> preference2[i];
    }

    // sort(preference2.begin(), preference2.end());

    int answer = 0;
    int prevp = 0;

    auto it1 = preference1.begin();
    auto it2 = preference2.begin();
    while(it1 != preference1.end() && it2 != preference2.end()) {
        // both like it?
        if(*it1 == *it2) {
            answer++;
            prevp = 0;
            it1++;
            it2++;
            continue;
        }

        // can p1 watch this movie?
        if(*it1 < *it2) {
            if(prevp != 1) {
                answer++;
                prevp = 1;
            }
            it1++;
            continue;
        }

        // can p2 watch this movie?
        if(*it2 < *it1) {
            if(prevp != 2) {
                answer++;
                prevp = 2;
            }
            it2++;
            continue;
        }
    }

    // if one list ends, we up one
    if(it1 != preference1.end() && prevp != 1) {
        answer++;
    }
    if(it2 != preference2.end() && prevp != 2) {
        answer++;
    }

    cout << answer << endl;
}
