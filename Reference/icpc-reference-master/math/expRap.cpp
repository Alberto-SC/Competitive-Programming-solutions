#include "template.hpp"

ll expRap(ll a,ll b,ll mod = oo){
	ll ans=1;
	while(b){
		if(b%2)ans = (ans*a) % mod;
		b /= 2;
		a = (a*a) % mod;
	}
	return ans;
}

int main(){
	cout << expRap(15,15) << endl;
}
