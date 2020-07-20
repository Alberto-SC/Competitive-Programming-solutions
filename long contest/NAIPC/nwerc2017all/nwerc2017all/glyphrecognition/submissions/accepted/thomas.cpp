#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

double Rmin[9], Rmax[9];

int main()
{	int n, i, x, y, k, best;
	double angle, phi, r, ratio, maxratio;
	double pi = acos(-1);
	scanf("%d", &n);
	for (k = 3; k <= 8; k++)
	{	Rmin[k] = 1e9;
		Rmax[k] = 0;
	}
	for (i = 0; i < n; i++)
	{	scanf("%d %d", &x, &y);
		angle = atan2(y, x);
		for (k = 3; k <= 8; k++)
		{	// Find segment that this vertex would be on
			phi = floor(angle*k/(2*pi)) * 2*pi/k + pi/k;
			// Calculate distance between segment and origin
			r = cos(phi)*x + sin(phi)*y;
			Rmin[k] = min(Rmin[k], r);
			Rmax[k] = max(Rmax[k], r);
		}
	}
	best = 0;
	maxratio = 0;
	for (k = 3; k <= 8; k++)
	{	ratio = Rmin[k]/Rmax[k]; // Note: area ~ r^2
		if (ratio > maxratio)
		{	best = k;
			maxratio = ratio;
		}
	}
	printf("%d %lf\n", best, pow(maxratio,2));
	return 0;
}