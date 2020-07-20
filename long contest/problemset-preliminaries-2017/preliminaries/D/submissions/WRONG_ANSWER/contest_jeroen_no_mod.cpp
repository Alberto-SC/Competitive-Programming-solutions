#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int64_t MOD = 10e9 + 7;

int main(){
	int64_t n;
	cin >> n;
	int64_t b = 1;
	for(int i = 0; i < n; i++){
		b *= 2;
		int64_t a;
		cin >> a;
		if(b < a) { cout << "error" << endl; return 0; }
		b -= a;
	}
	cout << b % MOD << endl;
	return 0;
}