#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
typedef unsigned long long int lli;

lli gauss(lli n){
	return n*(n+1)/2;
}

int main(){
	int t; cin >> t;
	while(t--){
		// cout << "test " << t << endl;
		lli a,b; cin >> a >> b;
		lli gcd = __gcd(a,b);
		a /= gcd;
		b /= gcd;


		lli val = floor(double(a)/double(b));
		// cout << a << "/" << b << "=" << val << endl;
		val *= 2;

		lli k1 = val;
		lli k2 = val+1;

		// cout << "K1=" << k1 << endl;
		// cout << "K1=" << k2 << endl;

		vector<pair<lli,lli>> sol;

		for(lli k=max(val-10,(lli)1); k < val+10; k++){
			lli lo=1, hi = k, mid;
			int it = 64;
			lli g = gauss(k), num, den=k-1;

			while(it--){
				mid = (lo+hi)>>1;
				den = k-1;
				num = g-mid;
				gcd = __gcd(num,den);
				num /= gcd;
				den /= gcd; 

				if(a == num && b == den){
					sol.push_back(make_pair(2,mid));
					break;
				}

				if(double(num)/double(den) > double(a)/double(b)){
					lo = mid;
				}else{
					hi = mid;
				}
			}
		}
		sort(sol.begin(), sol.end());
		cout << sol.size() << endl;
		for(auto p:sol){
			cout << p.first << " " << p.second << endl;
		}
	}



}