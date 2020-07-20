#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int64_t fill_all_but_one(int64_t N, int64_t &k, int64_t &ans){
	for(int i = 63; i >= 0; i--){
		if((1LL<<i) & N) { ans += (1LL<<i); k--;}
		if(k == 1) return (i-1);
	}
	return -1;
}

bool fill_last_one(int64_t N, int &i, int64_t &ans){
	while(i > 0 && (1LL<<i) & ((1LL<<i) + N) && (1LL<<(i-1) & ((1LL<<(i-1)) + N))){
		i--;
	}
	if((1LL<<i) & ((1LL<<i) + N)) {ans += (1LL<<i); return true;}
	if((1LL<<i) & N) return false;
}

void fix_last_one(int64_t N, int pos, int64_t k, int64_t &ans) {
	// int64_t k = 0;
	for(int i = pos; i <= 63; i++){
		if((1LL<<i) & ((1LL<<i) + N)) {ans += (1LL<<i); break;}
		if((1LL<<i) & ans) {ans -= (1LL<<i); k++;}
	}
	int i = 0;
	while(k){
		if((1LL<<i) & ((1LL<<i) + ans)) {ans += (1LL<<i); k--;}
		i++;
	}
	return;
}

void solve_just_one(int64_t N, int64_t k, int64_t &ans){
	for(int i = 63; i >= 0; i--){
		if((1LL<<i) &((1LL<<i) + N) and (1LL<<(i-1)) & N) {ans += (1LL<<i); return;}
	}
	return;
}

int main(){
	int64_t N, k;
	cin >> N >> k;
	int64_t ans = 0;
	if(k == 1) solve_just_one(N, k, ans);
	else{
		int pos = fill_all_but_one(N, k, ans);
		bool okey = false;
		// cout << pos << endl;
		if(pos > -1) okey = fill_last_one(N, pos, ans);
		pos = max(pos,0);
		if(!okey) {k--; fix_last_one(N, pos, k, ans);}
	}
	cout << ans << endl;
	return 0;
}