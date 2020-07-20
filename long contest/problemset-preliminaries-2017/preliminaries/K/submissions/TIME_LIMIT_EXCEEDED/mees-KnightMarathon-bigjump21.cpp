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

struct pt {
    long long x;
    long long y;
};

bool operator==(const pt& l, const pt& r) {
    return l.x == r.x && l.y == r.y;
}
bool operator<(const pt& l, const pt& r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

pt N, K, C;

vector<pt> nbs(pt p, bool bounds) {
    vector<long long> xs = {p.x+2, p.x+2, p.x+1, p.x-1, p.x-2, p.x-2, p.x-1, p.x+1};
    vector<long long> ys = {p.y-1, p.y+1, p.y+2, p.y+2, p.y+1, p.y-1, p.y-2, p.y-2};
    vector<pt> res;
    for(int i = 0; i < 8; i++) {
        if(!bounds || !(xs[i] < 0 || xs[i] >= N.x || ys[i] < 0 || ys[i] >= N.y)) {
            pt p1; p1.x = xs[i]; p1.y = ys[i];
            res.push_back(p1);
        }
    }
    return res;
}

int BFS(bool bounds) {
    map<pt, int> dist;
    dist[K] = 0;
    queue<pt> q;
    q.push(K);
    while(true) {
        pt cur = q.front(); q.pop();
        for(pt nb : nbs(cur, bounds)) {
            if(dist.find(nb) == dist.end()) {
                dist[nb] = dist[cur] + 1;
                if(nb == C) {
                    return dist[nb];
                }
                q.push(nb);
            }
        }
    }
}

int main() {
    cin >> N.x >> N.y >> K.x >> K.y >> C.x >> C.y;
    if(K == C) {
        cout << 0 << endl;
        return 0;
    }
    // Case 1: the capital is close. We can do straight BFS.
    if(abs(K.x - C.x) + abs(K.y - C.y) <= 200) {
        cout << BFS(true) << endl;
        return 0;
    }
    // Case 2: the capital is far away, so we can forget about bounds. We
    // simplify.
    C.x -= K.x;
    C.y -= K.y;
    K.x = 0;
    K.y = 0;
    if(C.x < 0) C.x = -C.x;
    if(C.y < 0) C.y = -C.y;
    if(C.x < C.y) {
        long long temp = C.x;
        C.x = C.y;
        C.y = temp;
    }

    int res;
    // Case 2.1: The castle's within 50 of the diagonal. "Area 1." You reduce
    // until your x-value is 100-ish.
    if(C.y + 50 >= C.x) {
        res = ((C.x)/3)*2;
        C.y -= ((C.x)/3)*3;
        C.x -= ((C.x)/3)*3;
    }
    // Case 2.2: You are above the 2-1 line. "Area 2." You use 3-3 steps until
    // you are on the 2-1 line-ish.
    else if(2*C.y > C.x) {
        long long overshot = 2*C.y - C.x;
        res = (overshot/3)*2;
        C.x -= (overshot/3)*3;
        C.y -= (overshot/3)*3;
    }
    // Case 2.3: You are below the box from above. "Area 4." Use 0-4 steps
    // until you reach lower x-coord.
    else if(C.y <= 50) {
        res = ((C.x - 100)/4)*2;
        C.x -= ((C.x - 100)/4)*4;
    }
    // Case 2.4: You are below the 2-1 line, but have y-coord greater than 50.
    // Use 0-4 steps to get onto the 2-1 line. "Area 3."
    else { 
        long long overshot = (C.x - 2*C.y);
        res = (overshot/4)*2;
        C.x -= (overshot/4)*4;
    }
    // Finally, if you're not close yet, you should at least be close to the
    // 2-1 line.
    if(C.x + C.y >= 200) {
        long long overshot = (C.x - 100)/4;
        res += overshot*2;
        C.x -= overshot*4;
        C.y -= overshot*2;
    }

    cout << res + BFS(false) << endl;
    return 0;
}
