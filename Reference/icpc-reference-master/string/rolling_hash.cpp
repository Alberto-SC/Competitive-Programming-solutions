const string A { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
const ll B = 41;            // Base = 41
const ll P = 1000000007;    // Prime = 10^9 + 7

ll fast_mod_exp(ll x, ll n, ll p) {
    ll y = 1, base = x;
    while (n) {
        if (n & 1) y = (y*x) % p;
        x = (x*x) % p;
        n >>= 1;
    }
    return y; // = x^n (mod p)
}

ll idA(char c) {
    return A.find(c);
}

// perfect when |A| can be represented in n bits and m <= 64/n
// wont be needed to check with patterns match
//ll hash_function2 (const string& s, int pos, ll prev, int m, int n) {
//    ll res = 0;
//
//    if (pos == 0) {
//        for (int i = 0; i < m; ++i) {
//            res <<= n;
//            res |= idA(s[i]);
//        }
//    } else {
//        ll mask = (1 << n*m) - 1;
//        res = ((prev << n) | idA(s[pos + m - 1])) & mask;
//    }
//
//    return res;
//}

// res = f(s[pos..pos + m - 1]), size = |A|, prev = f(s[pos-1..pos+m])
ll hash_function (const string& s, int pos, ll prev, int m) {
    ll res = 0;

    if (pos == 0) { // hash(S)=(∑(M,i=0) Si∗pi)%MOD
        for (int i = 0; i < m; ++i)
            res = (B*res + idA(s[pos + i])) % P;
    } else {
        ll SM = fast_mod_exp(B, m - 1, P);
        res = (prev - idA(s[pos - 1])*SM)*B + idA(s[pos+m-1]);
        res %= P;
    }

    return res;
}

int rolling_hash(const string& text, const string& pattern) {
    ll m = pattern.size(), n = text.size(), cnt = 0;
    ll r = hash_function(pattern, 0, 0, m), h = 0;

    for (int i = 0; i < n - m + 1; ++i) {
        h = hash_function(text, i, h, m);
        if (h == r and text.substr(i, m) == pattern) ++cnt;
    }

    return cnt;
}
