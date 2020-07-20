#include <iostream> 
#include <climits>
using namespace std;
unsigned long long bigmod(int b, int p, int m){
	if( p == 0) return 1;
	if( p %2 == 0){
		unsigned long long  mid = bigmod(b,p/2,m);
		return (mid*mid)%m;
	}
	else{
		unsigned long long mid = bigmod(b,p-1,m);
		return(b*mid)%m;
	}
}

int main(){
	unsigned long long b,p,m;
	b = 500;
	p = 8;
	m = ULLONG_MAX;
	cout<<bigmod(b,p,m);
}