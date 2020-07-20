#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    int N, C;
    cin >> N >> C;
    vector<pii> A(N);
    rep(i,0,N) {
        cin >> A[i].first >> A[i].second;
    }
    vi ai(N);
    iota(all(ai), 0);
    sort(all(ai), [&A](int a, int b) { return A[a].second < A[b].second; });
    vi res;
    trav(it, ai) {
        if (max(A[it].first, A[it].second) <= C) {
            res.push_back(it);
            C -= A[it].second;
        }
    }
    cout << sz(res) << endl;
    trav(it, res) cout << (it+1) << " ";
    cout << endl;
}
