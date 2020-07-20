// Solution of Raymond van Bommel
// Problem: Powers of 2

#include <iostream>

using namespace std;

long long N;
int k;

int NumberOfOnes(long long i) {
	int ret = 0;
	for(long long a = 1; a <= i; a *= 2)
		if((a & i) > 0) ret++;
	cerr << i << ": " << ret << endl;
	return ret;
}

long long LeastSignificantOne(long long i) {
	for(long long a = 1; a <= i; a *= 2)
		if((a & i) > 0) return a;
}

// Fixed by Ragnar for i=2^j-1 case
long long LeastSignificantZero(long long i) {
	long long a = 1;
	for(; a <= i; a *= 2)
		if((a & i) == 0) return a;
	return a;
}

int main() {
	cin >> N >> k;
	N++;
	while(NumberOfOnes(N) != k) {
		while(NumberOfOnes(N) > k) N += LeastSignificantOne(N);
		while(NumberOfOnes(N) < k) N += LeastSignificantZero(N);
	}
	cout << N << '\n';
	return 0;
}
