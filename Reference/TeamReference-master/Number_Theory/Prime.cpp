#include <bits/stdc++.h>
using namespace std;
const int N=16000000;
const int sqrtN=sqrt(N);
bool isP[N];

// O(N log log N)
void sieve(){
  fill(isP, isP+N, true);
  isP[0] = isP[1] = false;

  for(int i = 4;i < N;i += 2)
	  isP[i] = false;

  for(int i = 3;i < sqrtN; i += 2)
    if(isP[i])
    	for(int j = i*i; j < N; j += 2ll*i)
    		isP[j] = false;
}

/*
	Binary Multiplication
	[Tested Timus 1141,1204]**
*/
int mod_mult(int a, int b, int mod){
	int x = 0;
	while(b){
		if(b & 1)	x = (x + a) % mod;
		a = (a << 1) % mod;
		b >>= 1;
	}
	return x;
}

/*
	Binary Exponentiation
	[Tested Timus 1141,1204]**
*/
int mod_pow(int a, int n, int mod){
	int x = 1;
	while(n){
		if(n & 1)	x = mod_mult(x, a, mod);
		a = mod_mult(a, a, mod);
		n >>= 1;
	}
	return x;
}

/*
Miller Rabin
[Tested SPOJ PON]
*/
bool witness(int a, int s, int d, int n){
	int x = mod_pow(a, d, n);
	if (x == 1 || x == n - 1) return false;
	for(int i = 0; i < s - 1; i++)
	{
		x = mod_mult(x, x, n);
		if (x == 1) return true;
		if (x == n - 1) return false;
	}
	return true;
}

bool isPrime(int n)
{
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	int d = n - 1, s = 0;
	while (d % 2 == 0) ++s, d /= 2;
	int test[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 0};
	for (int i = 0; test[i] && test[i] < n; ++i)
		if (witness(test[i], s, d, n))
			return false; // composite
	return true; // probably prime
}


/*
Integer Factorization Pollard's Rho
*/
unsigned long long pollar_rho(unsigned long long n) //n shouldn't be prime
{
	if(!(n&1)) return 2;

	while(true)
	{
		unsigned long long x = (unsigned long long ) rand() % n, y = x, c = rand() % n;

		if(c == 0 || c == 2)
			c = 1;

		for(int i = 1, k = 2; ; i++)
		{
			x = mod_mult(x, x, n);
			if(x >= c) x -= c;
			else x+=n-c;
			if(x == n) x=0;
			if(x == 0) x = n-1;
			else x--;

			unsigned long long d = __gcd(x > y ? x - y : y - x, n);
			
			if(d == n) break;
			if(d != 1) return d;
			if(i == k)
			{
				y = x;
				k <<= 1;
			}
		}
	}
}


//fact primos de n
vector<pair<int,int> > fact(int n){
  vector<pair<int,int> > fp;
  for(int i = 2; i <= n; ++i){
    pair<int,int> pp = make_pair(i,0);
    while(!(n%i)){
    	n /= i;
    	pp.second++;
    }
    if(pp.second)
    	fp.push_back(pp);
  }
  if(n > 1)
	  fp.push_back(make_pair(n,1));
  return fp;
}


vector<int> primes;

//fact primos de n!
vector<pair<int,int> > factF(int n)
{
	vector<pair<int,int> > fp;
	int p;
	for(int i = 0; i < (int) primes.size(); ++i)
	{
		p = primes[i];
		if(p > n)
			break;

		int k = n;
		pair<int,int> pp = make_pair(p,0);
		while(k)
		{
			pp.second += k / p;
			k /= p;
		}
		fp.push_back(pp);
	}

	return fp;
}

/*
	Tested: SPOJ PRIME1, ETFS
	Complexity: O(n log log n)
*/

typedef long long ll;

// primes in [lo, hi)
vector<ll> primesR(ll lo, ll hi){
	const ll M = 1 << 14, SQR = 1 << 16;
	vector<bool> composite(M), small_composite(SQR);
	vector<pair<ll, ll>> sieve;
	for (ll i = 3; i < SQR; i += 2)
		if (!small_composite[i])
		{
			ll k = i * i + 2 * i * max(0.0, ceil((lo - i*i)/(2.0*i)));
			sieve.push_back({ 2 * i, k });
			for (ll j = i * i; j < SQR; j += 2 * i)
				small_composite[j] = 1;
		}
	vector<ll> ps;
	if (lo <= 2)
	{
		ps.push_back(2);
		lo = 3;
	}
	for (ll k = lo | 1, low = lo; low < hi; low += M)
	{
		ll high = min(low + M, hi);
		fill(composite.begin(), composite.end(), 0);
		for (auto &z : sieve)
			for (; z.second < high; z.second += z.first)
				composite[z.second - low] = 1;
		for (; k < high; k += 2)
			if (!composite[k - low])
				ps.push_back(k);
	}
	return ps;
}

int main(){

	vector<ll> prim;
	prim = primesR(1000000,10000000);
	pollar_rho(1000000000000036);
	return 0;
}