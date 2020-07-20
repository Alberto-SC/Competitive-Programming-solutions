#include <bits/stdc++.h>

#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);

using namespace std;

typedef long long int lli;

int main(){
	int n,m; cin >> n >> m;
	vector< vector<pair<int,double>> > rel(n);
	vector<double> lolipops(m,0.0);

	double amount,percent; 
	int des,k;
	for(int i=0; i<n; i++){
		cin >> amount >> k;
		lolipops[i] = amount;
		while(k--){
			cin >> des >> percent;
			rel[i].emplace_back(des-1,percent);
		}
	}

	int it=1000;
	while(it--){
		for(int i=0; i<n; i++){
			for(auto d:rel[i]){
				lolipops[d.first] += lolipops[i]*d.second;
			}
			lolipops[i] = 0.0;
		}
	}

	for(int i=0; i<n; i++){
		cout << "0.0" << endl;
	}

	for(int i=n; i<m; i++){
		cout << fixed << setprecision(8) << lolipops[i] << endl;
	}

	return 0;
}