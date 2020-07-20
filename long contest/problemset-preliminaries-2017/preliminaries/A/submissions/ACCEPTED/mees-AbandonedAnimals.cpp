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
    int n; cin >> n;
    vector<set<string>> park(n, set<string>());
    int k; cin >> k;
    for(int i = 0; i < k; i++) {
        int l; string s;
        cin >> l >> s;
        park[l].insert(s);
    }
    int l; cin >> l;
    vector<string> bro(l);
    vector<int> forward(l,-1), back(l,-1);
    for(int i = 0; i < l; i++) {
        cin >> bro[i];
    }
    int idx = 0;
    for(int i = 0; i < n; i++) {
        while(park[i].find(bro[idx]) != park[i].end()) {
            forward[idx] = i;
            idx++;
            if(idx == l)
                goto next;
        }
    }
    next:
    idx = l-1;
    for(int i = n-1; i >= 0; i--) {
        while(park[i].find(bro[idx]) != park[i].end()) {
            back[idx] = i;
            idx--;
            if(idx == -1)
                goto done;
        }
    }
    done:
    if(back[0] == -1) {
        cout << "impossible" << endl;
    }
    else if(forward == back) {
        cout << "unique" << endl;
    }
    else {
        cout << "ambiguous" << endl;
    }
    return 0;
}
