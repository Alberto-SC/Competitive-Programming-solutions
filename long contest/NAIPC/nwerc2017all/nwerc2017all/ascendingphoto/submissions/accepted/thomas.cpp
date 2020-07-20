// OBSERVATIONS
// When two or more people of the same height are next to each other,
//   it is never necessary to make a cut between them.
// When two people of consecutive heights are next to each other (in order),
//   a cut may not be necessary.
// When one or more people of the same height are flanked by people of
//   neighboring heights, one must make a cut on either side,
//   unless those people are all the people with that height.

// ALGORITHM
// Find all series of people of consecutive heights
//   (for which no intermediate height is represented fully)
// Loop over each height transition, see if there is an appropriate series
//   that can be used to avoid a cut.

// Complexity: O(n * log(n))

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int nmax = 1000000;

int Height[nmax];
unordered_map<int,int> NewH;
set<int> Present;
int Nr[nmax+1];
multiset<pair<int,int> > Series;

int main()
{	int n, m, i, h, start, cuts;
	multiset<pair<int,int> >::iterator it, it2;

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
  for (int h : Present)
    NewH[h] = m++;
	for (i = 0; i < n; i++)
		Height[i] = NewH[Height[i]];

	// Count number of occurrences per height
	memset(Nr, 0, sizeof(Nr));
	for (i = 0; i < n; i++)
		Nr[Height[i]]++;

	// Find series of consecutive heights
	start = -1;
	for (i = 0; i < n; i++)
	{	h = Height[i];
		// Check for range end
		if (start >= 0 && (i == n-1 || Height[i+1] != h+1 || Nr[h] == 1))
		{	Series.insert(make_pair(start, h));
			start = -1;
		}
		// No range
		if (i == n-1 || Height[i+1] != h+1)
			start = -1;
		// New range
		else if (start == -1)
			start = h;
		// else: range continues
	}

	cuts = n-1; // Default: cuts between everyone
	h = 0;
	while (!Series.empty())
	{	it = Series.begin();
		// Range start too small: update range
		if (it->first < h)
		{	if (it->second > h)
				Series.insert(make_pair(h, it->second));
			Series.erase(Series.begin());
		}
		// Fast-forward h to start of next range
		// Range size is 1: use it for transition h -> h+1
		else if (it->second == (h = it->first) + 1)
		{	cuts--;
			h++;
			Series.erase(Series.begin());
		}
		else
		{	// Look at the next range
			it2 = it;
			it2++;
			// Both ranges start at h: use one for transition h -> h+1,
			//   the other for h+1 -> h+2
			if (it2 != Series.end() && it2->first == h)
			{	cuts -= 2;
				if (it->second > h+2)
					Series.insert(make_pair(h+2, it->second));
				if (it2->second > h+2)
					Series.insert(make_pair(h+2, it2->second));
				h += 2;
				Series.erase(Series.begin());
				Series.erase(Series.begin());
			}
			// Only one range starts at h: use it for transition h -> h+1
			// Note: we cannot use it for h+1 -> h+2 anymore
			else
			{	cuts--;
				if (it->second > h+2)
					Series.insert(make_pair(h+2, it->second));
				h++;
				Series.erase(Series.begin());
			}
		}
	}

	// Output
	printf("%d\n", cuts);
	return 0;
}
