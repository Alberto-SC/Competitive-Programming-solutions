#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef int ret_t;

struct NearbySquare {
	NearbySquare(int _x, int _y, int _moves) : x(_x), y(_y), moves(_moves) {}
	int x, y, moves;
};

class Solver {
  public:
	/* Idea behing this solution: A large part of the knight's journey
	   will consist of just two types of moves: either (+2,+1) and
	   (+2,-1), or (+2,+1) and (+1,+2) (as well as symmetric copies of
	   these pairs of moves). If two squares are connected using just
	   moves of one of these pairs, we can check this and compute the
	   number of moves in constant time. There are always squares
	   close to the knight's starting location and the capital that
	   are connected in this way; these squares can be enumerated
	   using any search algorithm.

	   Note: This problem is very different from pre-existing similar
	   problems, because it requires a different solution (outlined
	   above). Similar problems that I'm aware of are:

	   - One from Topcoder:
	     https://community.topcoder.com/stat?c=problem_statement&pm=2926&rd=5853
	     This uses an infinite chessboard, so that you don't need to
	     worry about boundaries at all and the distance can be
	     computed by a single constant-time function.

	   - Other problems using a large chessboard don't make it as
	     large as this problem (here it can be 1e9 x 1e9). On this
	     problem, any standard search algorithm will likely get TLE.
	     */
	int nx, ny;
	vector<NearbySquare> nearKnight;
	vector<NearbySquare> nearCapital;
	ret_t easy_dist(int dx, int dy) {
		/* Compute the knight's move distance between two squares
		   (dx,dy) apart, if they are connected by the two types of
		   moves described above. If they are not connected in this
		   way, return -1. Note that the answer doesn't depend on
		   where the boundaries of the chessboard are: a sequences of
		   moves staying within the boundaries always exists. (This
		   wouldn't be true if the board could be just 1 square in one
		   of its dimensions.)
		*/
		dx = abs(dx);
		dy = abs(dy);
		if(dx > dy) swap(dx, dy);
		if(dx <= dy / 2) {
			/* If the squares are connected as required, it is by the
			   pair of moves (+1,+2) and (-1, +2)
			*/
			if(dy % 2 == 1) return -1;
			if((dx + dy / 2) % 2 == 1) return -1;
			return dy / 2;
		} else {
			/* In this case, the moves must be (+1,+2) and (+2,+1)
			 */
			if((dx + dy) % 3 != 0) return -1;
			return (dx + dy) / 3;
		}
	}
	void dfs(int x, int y, int moves, vector<NearbySquare> &nearbySquares) {
		if(x < 0 || y < 0 || x >= nx || y >= ny)
			// Off the edge of the board: stop
			return;
		nearbySquares.push_back(NearbySquare(x, y, moves));
		if(moves >= 2)
			// Only search a few moves around origin: 2 turns out to be enough
			return;
		// Otherwise, explore recursively
		for(int sign_x = -1; sign_x <= 1; sign_x += 2) {
			for(int sign_y = -1; sign_y <= 1; sign_y += 2) {
				dfs(x + 2 * sign_x, y + sign_y, moves + 1, nearbySquares);
				dfs(x + sign_x, y + 2 * sign_y, moves + 1, nearbySquares);
			}
		}
	}
	ret_t solve(int _nx, int _ny, int kx, int ky, int cx, int cy) {
		nx = _nx;
		ny = _ny;

		dfs(kx, ky, 0, nearKnight);
		dfs(cx, cy, 0, nearCapital);

		ret_t ret = 1e9;
		for(int i = 0; i < nearKnight.size(); ++i) {
			for(int j = 0; j < nearCapital.size(); ++j) {
				NearbySquare &A = nearKnight[i];
				NearbySquare &B = nearCapital[j];
				int d           = easy_dist(A.x - B.x, A.y - B.y);
				if(d < 0) continue;
				d += A.moves + B.moves;
				if(d < ret) ret = d;
			}
		}
		/* There will always be way for the knight to reach the
		   capital, unless the size of the board is only 2 in either
		   dimension, or 3x3. So for the limits in the problem
		   statement (at least 8x8), a solution will always be found
		   and we can just return it.
		 */
		return ret;
	}
};

int main(int argc, char **argv) {
	Solver solver;

	// *** get input ***
	int nx, ny, kx, ky, cx, cy;
	cin >> nx >> ny >> kx >> ky >> cx >> cy;
	ret_t ret = solver.solve(nx, ny, kx, ky, cx, cy);

	// *** give output ***
	cout << ret << endl;
	return 0;
}
