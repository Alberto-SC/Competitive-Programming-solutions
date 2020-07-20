#include <algorithm>
#include <cstdio>
using namespace std;

// Score after distributing wildcards (assumes a <= b <= c)
long long score (long long a, long long b, long long c)
{	return a*a+b*b+c*c+7*a;
}

int main()
{	int n, t;
	long long a, b, c, d, m, maxscore;
	scanf("%d", &n);
	for (t = 0; t < n; t++)
	{	scanf("%lld %lld %lld %lld", &a, &b, &c, &d);

		// Arrange for a <= b <= c
		if (a>b) swap(a,b);
		if (a>c) swap(a,c);
		if (b>c) swap(b,c);

		// All wildcards to c
		maxscore = score(a, b, c+d);

		// Increase a to m
		for (m = a+1; m <= b && m <= a+d && m <= a+3; m++)
			maxscore = max(maxscore, score(m, b, c+d+a-m));

		// Increase a and b to m
		for (m = b; 2*m <= a+b+d && 3*m <= a+b+c+d && m <= a+3; m++)
			maxscore = max(maxscore, score(m, m, a+b+c+d-2*m));

		printf("%lld\n", maxscore);
	}
}