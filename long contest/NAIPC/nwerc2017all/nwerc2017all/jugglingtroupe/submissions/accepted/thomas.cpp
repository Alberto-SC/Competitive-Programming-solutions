// OBSERVATIONS
// The order in which the people with multiple coins redistribute their coins
//   does not matter.
// The end configuration is all ones with some zeros.

// This program adds one person at a time.
// It keeps track of where the zeros (currently) are and how many coins have
//   been relegated to the right.
// These coins are added to the total of the newly added person (called it x).
// The end result of the redistribution of these coins is that x-1 coins go to
//   the right and the zeros combined move x-1 spaces to the right, starting
//   with the rightmost zero. Each time a zero reaches the far right, it
//   disappears and the coin excess decreases by one.
// When there are no more zeros, a new one "appears" on the far left
//   and the same procedure applies.

// The fact that this is "what happens" can be understood partly from the fact
//   that $\sum i*s_i$ is invariant. Moving the x-1 coins to the right increases
//   the second sum by x-1, while each zero move decreases it by one.

// Complexity: O(n)
// (In each loop, at most one zero is added, which is removed at most once.)

#include <cstdio>
#include <cstring>
using namespace std;

const int nmax = 1000000;

char S[nmax+1];
int Zeros[nmax];

int main()
{	int n, k, nz, excess, tomove, i;
	scanf("%s", S);
	n = strlen(S);
	excess = 0;
	nz = 0;

	// Add each person one at a time
	for (k = 1; k <= n; k++)
	{	excess += S[k-1]-'0';
		if (excess == 0)
		{	Zeros[nz++] = k;
			continue;
		}
		tomove = --excess;
		// Move the existing zeros
		while (nz > 0 && tomove >= k+1 - Zeros[nz-1])
		{	tomove -= k+1 - Zeros[nz-1];
			nz--;
			excess--;
		}
		if (nz > 0)
			Zeros[nz-1] += tomove;
		// All zeros gone: add new zero
		else if (tomove > 0)
		{	excess -= tomove/(k+1);
			if (tomove % (k+1))
				Zeros[nz++] = tomove % (k+1);
		}
	}

	// Output
	i = 0;
	for (k = 1; k <= n; k++)
	{	if (i < nz && k == Zeros[i])
		{	printf("0");
			i++;
		}
		else
			printf("1");
	}
	printf("\n");
	return 0;
}
