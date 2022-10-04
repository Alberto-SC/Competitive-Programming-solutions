#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvll;
typedef vector<ll> vll;
typedef vector<pii> vpii;

int t,n;
int a[2005];
int freq[20005][30];

void build(){
	forr(i,1,n){
		forr(j,1,26){
			freq[i][j] = freq[i-1][j];
			if(a[i] == j) freq[i][j]++;
		}
	}
//	forr(j,1,26){
//		forr(i,1,n)
//			cout << freq[i][j] << " ";
//		cout << endl;
//	}
}

int fr(int l, int r, int k){
	if(r < l) return 0;
	return freq[r][k] - freq[l-1][k];
}

int solve(){
	int res,aux,act,cont,l,r;
	res = 0;
	forr(i,1,n){
		forr(j,i,n){
			cont = 0;
			forr(k,1,26){
				cont = max(cont, fr(i,j,k) );
			}
//			cout << "cont: " << cont << endl;
			forr(k,1,26){
				l = fr(1,i-1,k);
				r = fr(j+1,n,k);
//				cout << "k: " << k << " ";
//				cout << "l: " << l << " ";
//				cout << "r: " << r << endl;
				aux = cont + 2*min(l,r);
				res = max(res,aux);
			}
		}
	}
	return res;
}

int main () {
	fastIO();
	cin >> t;
	while(t--){
		cin >> n;
		forr(i,1,n) cin >> a[i];
		build();
		cout << solve() << endl;
	}
	return 0;
}
