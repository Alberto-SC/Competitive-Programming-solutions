#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
typedef unsigned long long int lli;

vector<lli> ans;
lli lvl2,lvl3;
void findAnswer(lli n){
	//freopen("distribution.in", "r", stdin);
	//freopen("distribution.out", "w", stdout);

	if(n == 0)
		return;
	
	while((n&1) == 0){
		n /= 2;
		lvl2 *= 2;
	}
	lvl3 = 1;
	while(lvl3 < n){
		lvl3 *= 3;
	}
	if(lvl3 > n) lvl3 /= 3;

	ans.push_back(lvl2*lvl3);
	lvl2 *= 2;
	findAnswer((n-lvl3)/2);
}

int main(){
	int t; cin >> t;
	while(t--){
		ans.clear();
		lvl2 = 1;
		lli n; cin >> n;
		findAnswer(n);

		cout << ans.size() << endl;
        
		reverse(ans.begin(), ans.end());
		for(int i=0; i<ans.size()-1; i++)
			cout << ans[i] << " ";
		cout << ans.back() << endl;
	}

	return 0;
}