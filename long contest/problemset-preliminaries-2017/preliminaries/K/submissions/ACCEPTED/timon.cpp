#include <bits/stdc++.h>
using namespace std;

int d[11][11] = {
	{4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4},
	{3, 4, 3, 2, 3, 2, 3, 2, 3, 4, 3},
	{4, 3, 2, 3, 2, 3, 2, 3, 2, 3, 4},
	{3, 2, 3, 4, 1, 2, 1, 4, 3, 2, 3},
	{4, 3, 2, 1, 2, 3, 2, 1, 2, 3, 4},
	{3, 2, 3, 2, 3, 0, 3, 2, 3, 2, 3},
	{4, 3, 2, 1, 2, 3, 2, 1, 2, 3, 4},
	{3, 2, 3, 4, 1, 2, 1, 4, 3, 2, 3},
	{4, 3, 2, 3, 2, 3, 2, 3, 2, 3, 4},
	{3, 4, 3, 2, 3, 2, 3, 2, 3, 4, 3},
	{4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4}
};

int jumps(int dx, int dy) {
	if (dx > dy) swap(dx, dy);
	return min(
		((dy - 2 * dx) % 4 == 0 && (dy - 2 * dx) >= max(0, -4 * dx))
			? ((dy - 2 * dx) / 2 + dx) : 1e9,
		((2 * dx - dy) % 3 == 0 && (2 * dx - dy) >= 0 && (-dx + 2 * dy) >= 0)
			? (dx + dy) / 3 : 1e9);
}

int main() {
	int nx, ny, kx, ky, cx, cy;
	cin >> nx >> ny >> kx >> ky >> cx >> cy;
	
	if (nx - kx - 1 < kx) { kx = nx - kx - 1; cx = nx - cx - 1; }
	if (ny - ky - 1 < ky) { ky = ny - ky - 1; cy = ny - cy - 1; }
	if (kx > cx) { swap(kx, cx); swap(ky, cy); }

	if (kx == 0 && ky == 0 && cx == 1 && cy == 1) {
		cout << 4 << endl;
		return 0;
	}

	int ans = 1e9;
	for (int x = max(0, kx-5); x <= min(nx-1, kx+5); ++x)
	for (int y = max(0, ky-5); y <= min(ny-1, ky+5); ++y)
		ans = min(ans, d[x-kx+5][y-ky+5] + jumps(abs(x-cx), abs(y-cy)));
	cout << ans << endl;
}
