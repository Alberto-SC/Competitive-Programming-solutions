// Solution of Raymond van Bommel
// Problem: Bacteria

#include <iostream>

using namespace std;

long long n, b;
const long long maxB = 1L << 61;
const long long modP = 1000000007;

int main () {
	long long bact = 1;
	cin >> n;
	bool enoughbacteria = false;
	for (int i = 0; i < n; i++) {
		cin >> b;
		bact *= 2;
		if (bact > maxB)
			enoughbacteria = true;
		if ( enoughbacteria || (bact >= b) ) {
			bact -= b;
		} else {
			cout << "error\n";
			return 0;
		}
		if (enoughbacteria)
			bact %= modP;
	}
	bact %= modP;
	cout << bact << "\n";
	return 0;
}
