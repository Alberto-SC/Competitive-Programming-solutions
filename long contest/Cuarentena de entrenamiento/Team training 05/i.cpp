#include <bits/stdc++.h>

#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);

using namespace std;

typedef long long int lli;

int main(){
	int n,m; cin >> n >> m;
	vector<string> bad(n);
	for(auto &x:bad) cin >> x;

	map<char,char> eq;
	eq['0'] = 'O';
	eq['1'] = 'L';
	eq['2'] = 'Z';
	eq['3'] = 'E';
	eq['5'] = 'S';
	eq['6'] = 'B';
	eq['7'] = 'T';
	eq['8'] = 'B';

	string test;
	while(m--){
		cin >> test;
		for(int i=0; i<test.size(); i++){
			if(eq.count(test[i]) > 0){
				test[i] = eq[test[i]];
			}
		}

		bool isValid = true;
		for(auto b:bad){
			if(b.size() <= test.size()){
				for(int i=0; i<test.size()-b.size()+1; i++){
					if(b == test.substr(i, b.size())){
						isValid = false;
					}
				}
			}
		}
		
		if(isValid){
			cout << "VALID" << endl;
		}else{
			cout << "INVALID" << endl;
		}
	}

	return 0;
}