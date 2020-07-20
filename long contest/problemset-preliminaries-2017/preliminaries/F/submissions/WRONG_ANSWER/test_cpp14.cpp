#include <iostream>
#include <tuple>
using namespace std;

auto square(int n) { return n * n; }

int main() {
	cout << " " << endl;
	double x;
	// just read the first integer,
	// so this can't be optimized away
	cin >> x;
	cout << "square: " << square(x) << endl;

	auto lambda = [copy = x](auto y) { return y * copy; };
	cout << "lambda: " << lambda(x) << endl;

	tuple<string, int> t("hai", x);
	cout << "int: " << get<int>(t) << endl;
	cout << "str: " << get<string>(t) << endl;
	cout << "0: " << get<0>(t) << endl;
	cout << "1: " << get<1>(t) << endl;

	return 0;
}
