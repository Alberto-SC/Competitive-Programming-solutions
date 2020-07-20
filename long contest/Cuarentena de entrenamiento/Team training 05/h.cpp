#include <bits/stdc++.h>

#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);

using namespace std;

typedef long long int lli;

int main(){
	int n; cin >> n;
	vector<int> p1(2*n),p2;
	for(auto &x:p1) cin >> x;

	int ans = 0;
	while(!p1.empty()){
		if(p2.empty()){
			p2.push_back(p1.back());
			p1.pop_back();
		}else if(p1.back() == p2.back()){
			p1.pop_back();
			p2.pop_back();
		}else{
			p2.push_back(p1.back());
			p1.pop_back();
		}
		ans++;
	}

	if(p2.empty()){
		cout << ans << endl;
	}else{
		cout << "impossible" << endl;
	}

	return 0;
}