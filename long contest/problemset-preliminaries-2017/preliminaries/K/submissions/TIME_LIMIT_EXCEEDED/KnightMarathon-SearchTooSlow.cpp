#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef int ret_t;

struct Pos {
    Pos(int _x, int _y, int cx, int cy, int _moves)
        :x(_x), y(_y), moves(_moves) {
        int dx = abs(cx - x);
        int dy = abs(cy - y);
        if (dx > dy)
            swap(dx, dy);
        if (dx <= dy / 2)
            heurVal = moves + (dy + 1) / 2;
        else
            heurVal = moves + (dx + dy + 2) / 3;
    }
    int x, y, moves, heurVal;
};

class compare { // for queue
public:
    bool operator()(const Pos & a, const Pos & b) const {
        return a.heurVal > b.heurVal // here > means lower goes first
            || (a.heurVal == b.heurVal && a.moves < b.moves);
    }
};

struct pairhash {
public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const
    {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second)
            ^ (std::hash<U>()(x.second) << 8);
    }
};

class Solver {
public:
    /* Search algorithm (a version of A*) which is much slower than
       the other solution; this and similar solutions should get TLE
       when the board is large.
    */
    ret_t solve(int nx, int ny, int kx, int ky, int cx, int cy) {
        Pos p(kx, ky, cx, cy, 0);
        priority_queue<Pos, vector<Pos>, compare> q;
        unordered_map<pair<int, int>, int, pairhash> bestSol;
        q.push(p);
        bestSol[make_pair(kx, ky)] = 0;
        while (!q.empty()) {
            p = q.top();
            q.pop();
            if (p.x == cx && p.y == cy) {
                cerr << "Hash table size: " << bestSol.size() << endl;
                return p.moves;
            }
            int moves2 = p.moves + 1;
            for (int i = 0; i < 8; ++i) {
                int dx = (i & 4) ? 2 : 1;
                int dy = (i & 4) ? 1 : 2;
                if (i & 1)
                    dx = -dx;
                if (i & 2)
                    dy = -dy;
                int x2 = p.x + dx;
                int y2 = p.y + dy;
                if (x2 < 0 || y2 < 0 || x2 >= nx || y2 >= ny)
                    continue;
                pair<int, int> xy2 = make_pair(x2, y2);

                if (!bestSol.count(xy2) || bestSol[xy2] > moves2) {
                    bestSol[xy2] = moves2;
                    Pos p2(x2, y2, cx, cy, moves2);
                    q.push(p2);
                }
            }
        }

        return -1;
    }
};

int main(int argc, char ** argv) {
    string s;
    int N;
    getline(cin, s);
    {
        stringstream A(s);
        A >> N;
    }
    for (int no = 1; no <= N; ++no) {
        cerr //<< "Case "
            << no << " / " << N << endl;
        Solver solver;
        // *** get input ***
        getline(cin, s);
        int nx, ny, kx, ky, cx, cy;
        {
            stringstream A(s);
            A >> nx >> ny >> kx >> ky >> cx >> cy;
        }
        ret_t ret = solver.solve(nx, ny, kx, ky, cx, cy);

        // *** give output ***
        cout << ret << endl;
    }
    return 0;
}
