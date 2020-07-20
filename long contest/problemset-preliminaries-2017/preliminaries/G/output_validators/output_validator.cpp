#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>

int valid=42;
int invalid=43;

//
// this program assumes that the input of the relevant case is in the standard input
//
// This program needs one argument: the path to a file with the contestant solution
//
using namespace std;
typedef pair<int,int> ii;

//UFDS
vector<int> ranks(1000), parents(1000);
void create(int n){
    for(int i=0;i<n;i++){ ranks[i]=1; parents[i]=i;}
}
int find(int i){
    return (parents[i]==i)? i: (parents[i]=find(parents[i]));
}
void unionn(int i, int j){
    i=find(i); j= find(j);
    if(ranks[i]==ranks[j]) ranks[j]++;
    if(ranks[i]>ranks[j]) parents[j]=i;
    else parents[i]=j;
}

set<ii> keys_in, keys_contestant;

int solve(ifstream & input){
	//== read input
    int m,n;
    input>>m>>n;
    vector<vector<double> > probabilities(m);
    priority_queue<pair<double, ii> > q;

    for(int i=0; i<m; i++) {
        probabilities[i]= vector<double>(n);
        for (int j=0; j<n; j++)
            input>> probabilities[i][j];
    }
    for(int i=0; i<m; i++) {
        int len; input>> len;

        for(int k=0; k<len; k++) {
            int col; input>> col;

            q.push(make_pair(probabilities[i][col],ii(-i,-m-col)));
            keys_in.insert(ii(i, col));
        }
    }
    //== End read input
    int r, c;
    create(m+n); //UFDS
    vector<double> contestant_probs;
    int r_prev=-1, c_prev = -1;
    while (cin >> r >> c){
        if(r_prev == -1 || r_prev < r || (r_prev == r && c_prev < c )){
            r_prev = r;
            c_prev = c;
        }
        else return invalid;
        if (keys_in.find(ii(r,c)) == keys_in.end())//Check if contestant keys are keys that could have been pressed
          return invalid;
        if (find(r)==find(c+m)) //Check that there are no cycles
          return invalid;
        else{
            unionn(r, c+m);
        }
        contestant_probs.push_back(-probabilities[r][c]);
    }
    sort(contestant_probs.begin(), contestant_probs.end());

    //Solve the problem to see if the set of probabilities is the same
    create(m+n);
    vector<ii> sol;
    unsigned int idx = 0;

    while(!q.empty()) {
        ii edge=q.top().second;
        double prob = q.top().first;
        q.pop();
        edge.first=-edge.first; edge.second=-edge.second;
        if(find(edge.first)!= find(edge.second)) {
            if (idx >= contestant_probs.size() || -contestant_probs[idx] != prob){
              return invalid;
            }
            else
                idx++;
            unionn(edge.first, edge.second);
        }
    }
    if (idx == contestant_probs.size())
      return valid;

    return invalid;
}


int main(int argc, char* argv[]) {
	ifstream input;
	if (argc != 3){
		cout << "Usage: " << argv[0] << " input judgeanswer";
		return -1;
	}
	input.open(argv[1]);
	int ret = solve(input);
	input.close();
	return ret;
}
