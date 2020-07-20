#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
int64_t mod ( int64_t a , int64_t b ) { return (( a % b ) + b ) % b ; }
int64_t MAX = (1LL<<62) - 1 + (1LL<<62);
typedef pair<int64_t,int64_t> pii;
typedef pair<vector<int64_t>,vector<int64_t> > pvivi;
typedef pair<int64_t,vector<int64_t> > pivi;

//given relative prime a and b, calculate x s.t. a * x = 1 modulo b
int64_t mul_inv(int64_t a, int64_t b){
    int64_t x0 = 0, x1 = 1;
    if(b == 1) return 1;
    while(b)
    {
        int64_t q = a / b;
        int64_t t = b; b = a % b; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    return x1;
}

int64_t mulmod(int64_t a, int64_t b, int64_t m){
    if(abs(a) < abs(MAX / b)) { return a * b % m; }
    cout << a << " " << b << endl;
    cout << "dead" << endl; //Detects overflow -> WA solution.
    return __int128(a) * __int128(b) % m;
}


//Calculate the X that satisfies all a_i mod x_i and is smallest modulo product_i x_i
int64_t my_crt(vector<int64_t> a, vector<int64_t> x, int64_t limit){
    int64_t sum = 0, prod = 1;
    for(int64_t p : x) prod *= p;
    for(int64_t i = 0; i < a.size(); i++){
        int64_t p = prod / x[i];
        int64_t m = mul_inv(p, x[i]);
        // sum += mulmod( mulmod(a[i], m, prod), p, prod);
        sum += mod( mod(a[i] * m, prod) * p, prod);
    }
    return mod(sum,prod);
}

map<pii,int64_t> frogcnt; //count amount of frogs per modulo class
map<pii,int64_t> frogmax; //keep the largest position known per modulo class
map<int64_t,pii> frogbest; //Keep the largest modulo class per jump distance
map<int64_t,vector<int64_t> > frogties; //Keep all tied modulo classes per jump distance
set<int64_t> jump_distances;


int64_t ans = MAX;
//Given multiple buckets of elements, return all combinations of buckets.
void combinator2(map<int64_t, vector<int64_t> > &frogties, vector<int64_t> &a, vector<int64_t> &x, int64_t superd, int64_t pos){
    if( pos == frogties.size() ) {
        int64_t X = my_crt(a,x,ans);

        int64_t ans_pos = X;
        for(int64_t j = 0; j < x.size(); j++){
            int64_t p = x[j], c = a[j];
            int64_t maxpos = frogmax[{p,c}];
            int64_t k = ceil((double)(maxpos - X) / (double) superd);
            ans_pos = max(ans_pos, X + k * superd);
        }
        ans = min(ans,ans_pos);
        return;
    }

    int cnt = 0;
    pivi t;
    
    for(pivi p : frogties) {
        if(cnt == pos) t = p;
        cnt++;
    }

    x.push_back(t.first);
    for( int64_t k : t.second){
        a.push_back(k);
        combinator2(frogties,a,x,superd,pos + 1);
        a.pop_back();
    }
    x.pop_back();

}

void combinator3(vector<pair<int64_t, vector<int64_t> > > &frogties, vector<int64_t> &a, vector<int64_t> &x, int64_t superd, int64_t pos){
    if( pos == frogties.size() ) {
        int64_t X = my_crt(a,x,ans);

        int64_t ans_pos = X;
        for(int64_t j = 0; j < x.size(); j++){
            int64_t p = x[j], c = a[j];
            int64_t maxpos = frogmax[{p,c}];
            int64_t k = ceil((double)(maxpos - X) / (double) superd);
            ans_pos = max(ans_pos, X + k * superd);
        }
        ans = min(ans,ans_pos);
        return;
    }

    // int cnt = 0;
    // pivi t = frogties[pos];
    
    // for(pivi p : frogties) {
    //     if(cnt == pos) t = p;
    //     cnt++;
    // }

    x.push_back(frogties[pos].first);
    for( int64_t k : frogties[pos].second){
        if(frogmax[{frogties[pos].first,k}] >= ans) continue;
        a.push_back(k);
        combinator3(frogties,a,x,superd,pos + 1);
        a.pop_back();
    }
    x.pop_back();

}

pii combinator(map<int64_t,vector<int64_t> > &frogties){
    //Calculate product of primes and height.
    int64_t superd = 1, ans_height = 0;
    for(int64_t p : jump_distances) { superd *= p; ans_height += frogbest[p].second; }

    //Calculate amount of possibilities
    int64_t total = 1;
    for(pivi p : frogties) total *= p.second.size();

    int64_t ans = MAX;
    for(int64_t i = 0; i < total; i++){
        int64_t prod = 1;
        vector<int64_t> a, x;
        int64_t maxpos = 0;
        for(pivi p : frogties){
            int64_t pos = (i / prod) % p.second.size();
            a.push_back(p.second[pos]);
            x.push_back(p.first);
            maxpos = max(maxpos, frogmax[{p.first,p.second[pos]}]);
            prod *= p.second.size();
        }
        int64_t X = my_crt(a,x,ans);

        int64_t ans_pos = X;
        for(int64_t j = 0; j < x.size(); j++){
            int64_t p = x[j], c = a[j];
            int64_t maxpos = frogmax[{p,c}];
            int64_t k = ceil((double)(maxpos - X) / (double) superd);
            ans_pos = max(ans_pos, X + k * superd);
        }
        ans = min(ans,ans_pos);
    }
    return {ans,ans_height};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int64_t n;
    cin >> n;
    
    for(int64_t i = 0; i < n; i++){
        //Reading position x and jump distance d
        int64_t x, d;
        cin >> x >> d;
        jump_distances.insert(d);
        //Category jump distance d, pos x % d has one extra frog
        frogcnt[{d,x % d}]++;
        frogmax[{d,x % d}] = max(frogmax[{d,x % d}], x);
        //If this category is now the biggest, update best category for this jump distance.
        if(frogcnt[{d,x % d}] == frogbest[d].second) {
            //We found a tie, add it to the list
            frogties[d].push_back(x % d);
        }
        if(frogcnt[{d,x % d}] > frogbest[d].second) {
            //Save the best pair: (category offset, size of category)
            frogties[d] = vector<int64_t> ();
            frogties[d].push_back(x % d);
            frogbest[d] = {x % d, frogcnt[{d,x % d}]};
        }
    }


    //pii ans = combinator(frogties); //Find all possible CRT combinations
    int64_t superd = 1, ans_height = 0;
    for(int64_t p : jump_distances) { superd *= p; ans_height += frogbest[p].second; }
    vector<int64_t> a,x;
    vector<pair<int64_t,vector<int64_t> > > frogties2;
    for(pivi p : frogties){
        frogties2.push_back({p.first,p.second});
    }
    // combinator2(frogties,a, x, superd, 0);
    combinator3(frogties2,a, x, superd, 0);
    cout << ans << " " << ans_height << endl;
    return 0;
}