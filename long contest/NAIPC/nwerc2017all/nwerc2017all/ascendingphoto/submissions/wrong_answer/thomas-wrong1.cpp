// ALGORITHM
// Subtract one cut for every two neighbouring people
//   of the same height or of consecutive heights.

// Fails for e.g. 100 110 100 110,
//   since we can't keep both (100,110) pairs next to each other.
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

	cuts = 0;
	for (i = 0; i < n-1; i++)
		if (Height[i+1] != Height[i] && Height[i+1] != NextH[Height[i]])
			cuts++;

	printf("%d\n", cuts);
	return 0;
}
