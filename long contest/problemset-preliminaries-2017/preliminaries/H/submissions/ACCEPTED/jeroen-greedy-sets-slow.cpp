#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int MAX = 1000010;

set<int> readin(){
	int k;
	cin >> k;
	set<int> l;
	for(int i = 0; i < k; i++){
		int j;
		cin >> j;
		l.insert(j);
	}
	return l;
}

bool existsIn(int target, set<int> &l){
	return(l.find(target) != l.end());
}

int main(){

	set<int> l1 = readin(), l2 = readin();
	int ans = 0;
	int unhappy = 0;
	for(int i = 0; i < MAX; i++){
		if(!unhappy){
			if(existsIn(i,l1) && existsIn(i,l2)){ 	ans++; }
			else if(existsIn(i,l1)){ unhappy = 2; 		ans++; }
			else if(existsIn(i,l2)){ unhappy = 1;		ans++; }
		}
		else if(unhappy == 1 && existsIn(i,l1)){
			ans++;
			unhappy = 2;
			if(existsIn(i,l2)) unhappy = 0;
		}
		else if(unhappy == 2 && existsIn(i,l2)){
			ans++;
			unhappy = 1;
			if(existsIn(i,l1)) unhappy = 0;
		}
	}
	cout << ans << endl;

	return 0;
}