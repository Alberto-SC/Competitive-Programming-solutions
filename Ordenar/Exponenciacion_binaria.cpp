#include <iostream>

using namespace std;
long Exponenciar(long a, long n, long m) {
    long resultado = 1;
    for (; n; n >>= 1) {
        if (n & 1) resultado = (resultado * a) % m;
        a = (a * a) % m;
    }
    return resultado;
}

int main(){
	long n;
	cout<<	Exponenciar(3,2,2);
}
