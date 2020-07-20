#include <algorithm>
#include <cstdio>
using namespace std;

const int Rmax = 13, Nmax = 1 << Rmax;

int Rating[Nmax];
double Prob[Rmax+1][Nmax]; // Prob[r][i] = probability that player i reaches round r


int main()
{
	int n, N, R, r, i, j, first, last;
	scanf("%d", &n);

	// Find the largest power of 2 >= n (and the number of rounds)
	for (R = 0, N = 1; N < n; R++, N *= 2);

	// Store ratings into the back of the array
	for (i = 0; i < n; i++)
		scanf("%d", &Rating[N-n+i]);

	// Sort the ratings (apart from the first one)
	sort(Rating+(N-n+1), Rating+N);

	// Add byes (players with rating 0) and alternate with the weakest players
	for (i = 0; i < N-n; i++)
	{	Rating[2*i] = Rating[N-n+i];
		Rating[2*i+1] = 0;
	}

	// Calculate probabilities using DP
	for (i = 0; i < N; i++)
		Prob[0][i] = 1;
	for (r = 0; r < R; r++)
		for (i = 0; i < N; i++)
		{	Prob[r+1][i] = 0;
			if (Rating[i] > 0)
			{	// Loop over all possible opponents
				first = (((i>>r)^1)<<r);
				last = first + (1<<r);
				for (j = first; j < last; j++)
					Prob[r+1][i] += Prob[r][j] * Rating[i] / (Rating[i] + Rating[j]);
				Prob[r+1][i] *= Prob[r][i];
			}
		}

	// Output result
	printf("%.12lf\n", Prob[R][0]);
	return 0;
}
