#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
const int N = 1000000;
vector<lli>divi;
int lp[N+1];
vector<int> primes;
lli mod_pow(lli a,lli b,lli m){
    lli ans = 1;
    while(b){
        if(b&1) ans = (a*ans)%m;
        a = (a*a)%m;
        b>>=1;
    }
    return 0;
}
lli mod_mult(lli a, lli b, lli mod){
	lli x = 0;
	while(b){
		if(b & 1)	x = (x + a) % mod;
		a = (a << 1) % mod;
		b >>= 1;
	}
	return x;
}
void criba(){
    for (int i=2; i<=N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back (i);
        }
        for (int j=0; j<(int)primes.size() && primes[j]<=lp[i] && i*primes[j]<=N; ++j)
            lp[i * primes[j]] = primes[j];
    }
}

lli random(lli a, lli b) {
    lli intervallLength = b - a + 1;
    int neededSteps = 0;
    lli base = RAND_MAX + 1LL;
    while(intervallLength > 0){
    	intervallLength /= base;
    	neededSteps++;
    }
    intervallLength = b - a + 1;
    lli result = 0;
    for(int stepsDone = 0; stepsDone < neededSteps; stepsDone++){
        result = (result * base + rand());
    }
    result %= intervallLength;
    if(result < 0) result += intervallLength;
    return result + a; 
}
 
bool witness(lli a, lli n) {
    lli u = n-1;
    int t = 0;
    while (u % 2 == 0) {
        t++;
        u /= 2;
    }
    lli next = mod_pow(a, u, n);
    if(next == 1)return false;
    lli last;
    for(int i = 0; i < t; i++) {
    	last = next;
        next = mod_mult(last, last, n);//(last * last) % n;
        if (next == 1){
        	return last != n - 1;
        }
    }
    return next != 1;
}
 

bool isPrime(lli n, int s) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for(int i = 0; i < s; i++) {
        lli a = random(1, n-1);
        if (witness(a, n)) return false;
    }
    return true;
}
bool isSquare(lli val){
	lli lo = 1, hi = val;
	while(lo <= hi){
		lli mid = lo + (hi - lo) / 2;
		lli tmp = (val / mid) / mid; // be careful with overflows!!
		if(tmp == 0)hi = mid - 1;
		else if(mid * mid == val)return true;
		else if(mid * mid < val)lo = mid + 1;
	}
	return false;
}
lli countDivisors(lli n) {   
    lli ans = 1;
	for(int i = 0; i <(int) primes.size(); i++){
		if(n == 1)break;
		int p = primes[i];
		if(n % p == 0){ // checks whether p is a divisor of n
			int num = 0;
			while(n % p == 0){
				n /= p;
				++num;
			}
			// p^num divides initial n but p^(num + 1) does not divide initial val
			// => p can be taken 0 to num times => num + 1 possibilities!!
			ans *= num + 1;
		}
	}
    if(n == 1)return ans; // first case
	else if(isPrime(n,20))return ans * 2; // second case
	else if(isSquare(n))return ans * 3; // third case but with p == q
	else return ans * 4; // third case with p != q
} 
int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    criba();
    lli n,t;
    cin>>t;
    while(t--){
        cin>>n;
        lli nd = countDivisors(n);
        vector<lli> divs(nd);
        int cont = 0;
        for (int i=1; i<=sqrt(n);i++) { 
            if (n%i == 0) { 
                if (n/i == i) 
                    divs[nd/2] = i; 
                else {
                    divs[cont] = i; 
                    divs[(nd-1)-cont] = (n/i);
                    cont++; 
                } 
            }  
        }
        for(auto c:divs)cout<<c<<" ";
        cout<<"\n";
    }
    return 0;
}
