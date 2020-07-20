#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int MAX = 1000010;

void readin(vector<bool> &l){
	int k;
	cin >> k;
	for(int i = 0; i < k; i++){
		int j;
		cin >> j;
		l[j] = true;
	}
}

int main(){

	vector<bool> l1 (MAX), l2 (MAX);
	readin(l1);
	readin(l2);

	int ans = 0;
	bool ok1 = true, ok2 = true;
	
	for(int i = 0; i < MAX; i++){
		if(!l1[i] && !l2[i]) continue;
		if(ok1 && ok2){
			if(l1[i] && l2[i]) 	ans++;
			else if(l1[i]) {	ans++; ok2 = false; }
			else if(l2[i]) {	ans++; ok1 = false; }
		}
		else if(!ok1 && l1[i]){
			ok1 = true;
			ans++;
			ok2 = l2[i];
		}
		else if(!ok2 && l2[i]){
			ok2 = true;
			ans++;
			ok1 = l1[i];
		}
	}
	cout << ans << endl;
	
	return 0;
}