#include <bits/stdc++.h>
 
#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);
 
using namespace std;
 
typedef long long int lli;
 
int main(){
	int n; cin >> n;
	vector<int> v(n);
	for(auto &x:v) cin >> x;
 
	lli sum = 0;
	bool isSol;
	sort(v.begin(), v.end());
    do { 	
		isSol = true;
        sum = 0;
		for(auto i:v){
			sum += i;
			if(sum < 0 || sum > 99999999)
				isSol = false;
		}
		if(isSol){
			for(auto i:v)
				cout << i << endl;
			return 0;
		}
	}while(next_permutation(v.begin(), v.end()));
 
	cout << "Error" << endl;
 
	return 0;
}