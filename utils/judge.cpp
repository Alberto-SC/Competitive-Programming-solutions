#include "bits/stdc++.h"
using namespace std ;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int>ngen( 1, 1000000 ) ;


void sol(){
	int number = ngen( rng ) ;
	int queries = 25 ;
	while( queries-- ){
		int op, guess ;
		cin >> op >> guess ;
		if( op == 0 ){
		if( guess == number ){
			cout << "AC" << endl ;
			cout << "The number is " << number << endl ;
		}
		else{
			cout << -1 << " WA" << endl ;
			cout << "The number is " << number << endl ;
		}
		return ;
		}
		else{
		if( guess <= number ){
			cout << '<' << endl ;
		}
		else
			cout << '>' << endl ;
		}
	}
	cout << -1 << " WA" << endl ;
	cout << "The number is " << number << endl ;
}

signed main(){
	sol();
}