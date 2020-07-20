// Solution of Raymond van Bommel
// Problem: Proofs

#include <cassert>
#include <iostream>

using namespace std;

int p[20];
long long proofneeds[20][10];
long long prooflen[20][10];
long long totalprooflen[1048576];
int whichproof[1048576][2];
int n;
long long minlength = 123456789LL;
int bestsubset      = -1;

void dp(long long subset) {
	whichproof[subset][0] = whichproof[subset][1] = -1;
	for(int i = 0; i < n; i++) {
		// cerr << (1LL << i) << " & " << subset << " = " << ((1LL << i) & (subset)) << '\n';
		if(((1LL << i) & (subset)) > 0) {
			// cerr << "Subset " << subset << " contains " << i << '\n';
			for(int j = 0; j < p[i]; j++) {
				// cerr << "Considering proof " << j << " for theorem " << i << '\n';
				if(((subset) & (proofneeds[i][j])) == proofneeds[i][j]) {
					// cerr << "Proof can be applied.\n";
					if((totalprooflen[subset - (1LL << i)] + prooflen[i][j]) <
					   totalprooflen[subset]) {
						totalprooflen[subset] = totalprooflen[subset - (1LL << i)] + prooflen[i][j];
						whichproof[subset][0] = i;
						whichproof[subset][1] = j;
					}
					if(((1 & subset) == 1) && (totalprooflen[subset] < minlength)) {
						minlength  = totalprooflen[subset];
						bestsubset = subset;
					}
				}
			}
		}
	}
	// cerr << "For subset " << subset << " the shortest proof length is " << totalprooflen[subset];
	// cerr << " using proof " << whichproof[subset][1] << " for theorem " << whichproof[subset][0]
	// << '\n';
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> p[i];
		for(int j = 0; j < p[i]; j++) {
			cin >> prooflen[i][j];
			proofneeds[i][j] = 0;
			int k;
			cin >> k;
			for(int i2 = 0; i2 < k; i2++) {
				int di;
				cin >> di;
				// di--;
				proofneeds[i][j] += (1LL << di); // Assuming the di are distinct and unequal to i.
			}
		}
	}

	for(int s = 0; s < (1LL << n); s++) {
		totalprooflen[s]            = 123456789LL;
		if(s == 0) totalprooflen[s] = 0;
		dp(s);
	}

	assert(bestsubset > -1);
	cout << minlength << '\n';

	/*
	// REMOVED BY RAGNAR; the length is all we ask for
	int finalproofused[n];
	for (int i = 0; i < n; i++)
	    finalproofused[i] = 0;
	while (bestsubset > 0) {
	    int i = whichproof[bestsubset][0];
	    int j = whichproof[bestsubset][1];
	    finalproofused[i] = j + 1;
	    bestsubset -= (1LL << i);
	}
	for (int i = 0; i < n; i++)
	    cout << finalproofused[i] << '\n';
	*/

	return 0;
}
