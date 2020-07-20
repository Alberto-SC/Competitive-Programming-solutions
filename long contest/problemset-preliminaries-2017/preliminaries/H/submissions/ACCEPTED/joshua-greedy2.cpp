#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    int n1;
    int n2;
    int maxday = 0;

    vector<bool> preference1(1000000+5);
    vector<bool> preference2(1000000+5);

    cin >> n1;
    for(int i = 0; i < n1; ++i) {
        int j;
        cin >> j;
        preference1[j] = true;
        maxday = max(maxday, j);
    }

    cin >> n2;
    for(int i = 0; i < n2; ++i) {
        int j;
        cin >> j;
        preference2[j] = true;
        maxday = max(maxday, j);
    }

    int answer = 0;
    int prevp = 0;

    for(int i = 0; i <= maxday; ++i) {
        if(preference1[i] && preference2[i]) {
            answer++;
            prevp = 0;
            continue;
        }

        if(preference1[i] && prevp != 1) {
            answer++;
            prevp = 1;
            continue;
        }

        if(preference2[i] && prevp != 2) {
            answer++;
            prevp = 2;
            continue;
        }
    }

    cout << answer << endl;
}
