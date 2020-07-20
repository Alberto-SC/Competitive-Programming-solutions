#include <stdio.h>
#include <cmath>
#include <limits.h>
typedef long long ull;
int main(){
	bool sb = false;
    ull var = 226564566345;
    ull contador;
    for(contador = (ull)LLONG_MAX+1; contador > 0; contador >>= 1)	
        if(contador & var) printf("1"),sb = true;
        else if(sb) printf("0");
    return 0;
}