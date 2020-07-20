// ALGORITHM
// Subtract one cut for every two neighbouring people of consecutive heights.
// First consider "stand-alone" pairs (not conjoined with another pair,
//   then fill in the blanks.

// Fails for e.g. 100 110 120 100 110 120 130,
//   since it ends up keeping the first (100,110) pair together,
//   while it's the second pair that needs to stay together.
// (Correct answer: 3   Answer given: 4)

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
using namespace std;

const int nmax = 1000000;
const int hmax = 20000000;

int Height[nmax];
map<int,int> NewH;
map<int,int> Nr;
set<int> Present;
bool Double[nmax];
set<int> Used;

int main()
{	int n, m, i, h, cuts;

	// Read input, ignore repeated heights
	scanf("%d", &m);
	n = 0;
	for (i = 0; i < m; i++)
	{	scanf("%d", &h);
		if (n == 0 || h != Height[n-1])
			Height[n++] = h;
	}

	// Map all heights to consecutive integers
	for (i = 0; i < n; i++)
		Present.insert(Height[i]);
	m = 0;
	for (auto h : Present)
		NewH[h] = m++;
	for (i = 0; i < n; i++)
		Height[i] = NewH[Height[i]];

	// Count number of occurrences per height
	for (i = 0; i < n; i++)
		Nr[Height[i]]++;

	// Identify "conjoined" pairs
	for (i = 1; i < n-1; i++)
	{	h = Height[i];
		if (Height[i-1] == h-1 && Height[i+1] == h+1 && Nr[h] > 1)
			Double[i] = true;
	}

	// Make use of "stand-alone" pairs
	cuts = n-1;
	for (i = 0; i < n-1; i++)
	{	h = Height[i];
		if (Height[i+1] == h+1 && !Used.count(h) && !Double[i] && !Double[i+1])
		{	cuts--;
			Used.insert(h);
		}
	}

	// Make use of "conjoined" pairs
	for (i = 0; i < n-1; i++)
	{	h = Height[i];
		if (Height[i+1] == h+1 && !Used.count(h) && (Double[i] || Double[i+1]))
		{	cuts--;
			Used.insert(h);
			Double[i+1] = false;
		}	
	}

	printf("%d\n", cuts);
	return 0;
}
