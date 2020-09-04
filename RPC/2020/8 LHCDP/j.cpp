#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
typedef unsigned long long int  ull;
typedef long long int lli;
ull mulMod( ull a,ull b,ull m){
    ull res = 0, tmp = a % m;
    while (b){
        if (b & 1){
            res = res + tmp;
            res = (res >= m ? res - m : res);
        }
        b >>= 1;
        tmp <<= 1;
        tmp = (tmp >= m ? tmp - m : tmp);
    }
    return res;
}

lli powMod(lli a,lli b,lli m){
    lli res = 1 % m, tmp = a % m;
    while (b){
        if (b & 1)
            res = mulMod(res, tmp, m);
        tmp = mulMod(tmp, tmp, m);
        b >>= 1;
    }
    return res;
}

bool millerRabin(lli n){
    int a[5] = { 2, 3, 7, 61, 24251 };
    if (n == 2) return true;
    if (n == 1 || (n & 1) == 0) return false;
    lli b = n - 1;
    for (int i = 0; i < 5; i++){
        if (a[i] >= n) break;
        while ((b & 1) == 0) b >>= 1;
        lli t = powMod(a[i], b, n);
        while (b != n - 1 && t != 1 && t != n - 1){
            t = mulMod(t, t, n);
            b <<= 1;
        }
        if (t == n - 1 || (b & 1)) continue;
        else return false;
    }
    return true;
}

lli gcd(lli a, lli b){
    while (b > 0){
        lli t = a % b;
        a = b;
        b = t;
    }
    return a;
}

lli pollard_rho(lli n){
    lli x = 2 % n, y = x, k = 2, i = 1;
    lli d = 1;
    while (true){
        i++;
        x = (mulMod(x, x, n) + 1) % n;
        d = gcd((y - x + n) % n, n);
        if (d > 1 && d < n)
            return d;
        if (y == x){
            lli d = 2;
            while (n % d) d++;
            return d;
        }
        if (i == k){
            y = x;
            k <<= 1;
        }
    }
}

lli factors[1000], fCount;

void _factorize(lli n){
    if (n <= 1) return;
    if (millerRabin(n)){
        factors[ fCount++ ] = n;
        return;
    }
    lli d = pollard_rho(n);
    _factorize(d);
    _factorize(n/d);
}

void factorize(lli n){
    fCount = 0;
    _factorize(n);
    sort(factors, factors + fCount);
}

int main(){__
    int t;
    cin >> t;
    while (t--){
        lli n;
        cin >> n;
        factorize(n);
        for (int i = 0; i < fCount; i++){
            if(i==fCount-1)
                cout<<factors[i];
            else
                cout<<factors[i]<<" ";
        }
		cout<<endl;
    }
    return 0;
}