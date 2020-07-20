import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Solver{

    public int nx, ny;
	public ArrayList<NearbySquare> nearKnight = new ArrayList<NearbySquare>();
	public ArrayList<NearbySquare> nearCapital = new ArrayList<NearbySquare>();


    public class NearbySquare {
        public int x, y, moves;

        NearbySquare(int x, int y, int moves){
            this.x = x;
            this.y = y;
            this.moves = moves;
        }
    }
    int easy_dist(int dx, int dy) {
        /* Compute the knight's move distance between two squares
           (dx,dy) apart, if they are connected by the two types of
           moves described above. If they are not connected in this
           way, return -1. Note that the answer doesn't depend on
           where the boundaries of the chessboard are: a sequences of
           moves staying within the boundaries always exists. (This
           wouldn't be true if the board could be just 1 square in one
           of its dimensions.)
        */
        dx = Math.abs(dx);
        dy = Math.abs(dy);
        if (dx > dy){
        	int aux = dx;
        	dx = dy;
        	dy = aux;	
        }
        if (dx <= dy / 2) {
            /* If the squares are connected as required, it is by the
               pair of moves (+1,+2) and (-1, +2)
            */
            if (dy % 2 == 1)
                return -1;
            if ((dx + dy / 2) % 2 == 1)
                return -1;
            return dy / 2;
        }
        else {
            /* In this case, the moves must be (+1,+2) and (+2,+1)
             */
            if ((dx + dy) % 3 != 0)
                return -1;
            return (dx + dy) / 3;
        }
    }

    public void dfs(int x, int y, int moves, ArrayList<NearbySquare> nearbySquares) {
        if (x < 0 || y < 0 || x >= nx || y >= ny)
            // Off the edge of the board: stop
            return;
        nearbySquares.add(new NearbySquare(x, y, moves));
        if (moves >= 2)
            // Only search a few moves around origin: 2 turns out to be enough
            return;
        // Otherwise, explore recursively
        for (int sign_x = -1; sign_x <= 1; sign_x += 2) {
            for (int sign_y = -1; sign_y <= 1; sign_y += 2) {
                dfs(x + 2 * sign_x, y + sign_y, moves + 1, nearbySquares);
                dfs(x + sign_x, y + 2 * sign_y, moves + 1, nearbySquares);
            }
        }
    }

    public int solve(int _nx, int _ny, int kx, int ky, int cx, int cy) {
        nx = _nx;
        ny = _ny;

        dfs(kx, ky, 0, nearKnight);
        dfs(cx, cy, 0, nearCapital);

        int ret = (int) 1e9;
        for (int i = 0; i < nearKnight.size(); ++i) {
            for (int j = 0; j < nearCapital.size(); ++j) {
                NearbySquare A = nearKnight.get(i);
                NearbySquare B = nearCapital.get(j);
                int d = easy_dist(A.x - B.x, A.y - B.y);
                if (d < 0)
                    continue;
                d += A.moves + B.moves;
                if (d < ret)
                    ret = d;
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

    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	    String[] words;
	    
        int _nx,  _ny,  kx,  ky,  cx,  cy;
	    words = br.readLine().split("\\s");
        _nx = Integer.parseInt(words[0]);
        _ny = Integer.parseInt(words[1]);
	    words = br.readLine().split("\\s");
        kx = Integer.parseInt(words[0]);
        ky = Integer.parseInt(words[1]);
	    words = br.readLine().split("\\s");
        cx = Integer.parseInt(words[0]);
        cy = Integer.parseInt(words[1]);
        Solver s = new Solver();
        int ret = s.solve(_nx,  _ny,  kx,  ky,  cx,  cy);
        System.out.println(ret);
   }
}
