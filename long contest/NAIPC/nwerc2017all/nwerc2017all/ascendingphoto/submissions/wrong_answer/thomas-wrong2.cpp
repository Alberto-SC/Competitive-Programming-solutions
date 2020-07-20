// ALGORITHM
// Subtract one cut for every two neighbouring people of the same height
//   or of consecutive heights.
// Keep track of height pairs already used.

// Fails for e.g. 100 110 120 110,
//   since we can't keep both (100,110) and (110,120) next to each other,
//   since the other 110 needs to be put in there as well.
// (Correct answer: 2   Answer given: 1)

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
using namespace std;

const int nmax = 1000000;
const int hmax = 20000000;

int Height[nmax];
map<int,int> NextH;
set<int> Present;
set<int> Used;

int main()
{	int n, i, j, cuts;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &Height[i]);

	// Identify next height for each height
	for (i = 0; i < n; i++)
		Present.insert(Height[i]);
	i = -1;
	for (auto i = Present.rbegin(), j = i; i != Present.rend(); j=i++) {
		NextH[*i] = (i == j ? hmax+1 : *j);
	}

	cuts = n-1;
	for (i = 0; i < n-1; i++)
	{	if (Height[i+1] == Height[i])
			cuts--;
		else if (Height[i+1] == NextH[Height[i]] && !Used.count(Height[i]))
		{	cuts--;
			Used.insert(Height[i]);
		}
	}

	printf("%d\n", cuts);
	return 0;
}
