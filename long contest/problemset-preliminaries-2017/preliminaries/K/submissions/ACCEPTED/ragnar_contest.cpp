#include <iostream>
using namespace std;
int main() {
	int nx, ny, kx, ky, cx, cy;
	cin >> nx >> ny >> kx >> ky >> cx >> cy;
	int x = abs(cx - kx), y = abs(cy - ky);
	if(x < y) swap(x, y), swap(nx, ny), swap(cx, cy), swap(kx, ky); // now we know that x>=y>=0
	if(x == 1 && y == 0) return cout << 3 << endl, 0;
	if(x == 2 && y == 2) return cout << 4 << endl, 0;
	if(x == 1 && y == 1 && (((cx == 0 || cx == nx - 1) && (cy == 0 || cy == ny - 1)) ||
	                        ((kx == 0 || kx == nx - 1) && (ky == 0 || ky == ny - 1))))
		return cout << 4 << endl, 0;
	int steps = max((x + y + 2) / 3, (x + 1) / 2);
	return cout << steps + ((x + y + steps) & 1) << '\n', 0; // fix parity
}
