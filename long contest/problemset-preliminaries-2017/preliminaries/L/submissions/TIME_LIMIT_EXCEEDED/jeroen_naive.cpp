#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int64_t,int64_t> pii;
typedef pair<vector<int64_t>,vector<int64_t> > pvivi;
typedef pair<int64_t,vector<int64_t> > pivi;

vector<pvivi> combinator(map<int64_t,vector<int64_t> > frogties){
    int64_t total = 1;
    for(pivi p : frogties) total *= p.second.size();
    // cout << total << endl;
    // printFrogties(frogties);
    vector<pvivi> possibilities (total);
    for(int64_t i = 0; i < total; i++){
        int64_t prod = 1;
        for(pivi p : frogties){
            int64_t pos = (i / prod) % p.second.size();
            possibilities[i].first.push_back(p.second[pos]);
            possibilities[i].second.push_back(p.first);
            prod *= p.second.size();
        }
    }
    return possibilities;
}

int main(){

    ios::sync_with_stdio(false); cin.tie(0);

	int64_t n;
	cin >> n;
    // cout << n << endl;
    map<pii,int64_t> frogcnt;
    map<pii,int64_t> frogmax;
    map<int64_t,pii> frogbest;
    map<int64_t,vector<int64_t> > frogties;
    set<int64_t> jump_distances;
    for(int64_t i = 0; i < n; i++){
        //Reading position x and jump distance d
    	int64_t x, d;
    	cin >> x >> d;
        jump_distances.insert(d);
        //Category jump distance d, pos x % d has one extra frog
        frogcnt[{d,x % d}]++;
        frogmax[{d,x % d}] = max(frogmax[{d,x % d}], x);
        //If this category is now the biggest, update best category for this jump distance.
        if(frogcnt[{d,x % d}] == frogbest[d].second) {
            frogties[d].push_back(x % d);
        }
        if(frogcnt[{d,x % d}] > frogbest[d].second) {
            //Save a pair: (category offset, size of category)
            frogties[d] = vector<int64_t> ();
            frogties[d].push_back(x % d);
            frogbest[d] = {x % d, frogcnt[{d,x % d}]};
        }
    }

    int64_t ans_height = 0,
    		largest_pos = 0,
            step = 1,
            mempos = 0;
    for(int64_t p : jump_distances) ans_height += frogbest[p].second;

    vector<pvivi > poss = combinator(frogties);
    vector<int64_t> answers;
    // cout << poss.size() << endl;
    for(pvivi t : poss) {
        vector<int64_t> a = t.first;
        vector<int64_t> x = t.second;
        largest_pos = 0;
        for(int64_t j = 0; j < x.size(); j++){
            int64_t p = x[j], c = a[j];
            largest_pos = max(frogmax[{p,c}],largest_pos);
        }
        step = 1; mempos = largest_pos;
        for(int64_t j = 0; j < x.size(); j++){
            while(largest_pos % x[j] != a[j]) largest_pos += step;
            step *= x[j];
        }
        int64_t k = ceil((double)(mempos - largest_pos) / (double) step);
        int64_t ans = largest_pos - k * step;
        answers.push_back(ans);
    }
    sort(answers.begin(),answers.end());
    cout << answers[0] << " " << ans_height << endl;
    // for(auto i : jump_distances){
    // 	ans_height += frogbest[i].second;
    // 	largest_prime = i;
    // 	largest_pos = max(largest_pos,frogmax[{i,frogbest[i].first}]);
    // }
    // int64_t step = 1, mem_pos = largest_pos;
    // for(auto i : jump_distances){
    // 	if(frogbest[i].second == 0) continue;
    // 	while(largest_pos % i != frogbest[i].first) largest_pos += step;
    // 	step *= i;
    // }
    // while(largest_pos - step >= mem_pos) largest_pos -= step;

   	// cout << largest_pos << " " << ans_height << endl;

	return 0;
}