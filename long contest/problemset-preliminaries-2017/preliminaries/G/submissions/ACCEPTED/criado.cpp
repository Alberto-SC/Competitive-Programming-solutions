#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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

int main() {
  int m,n;
  cin>>m>>n;

  vector<vector<double> > probabilities(m);
  priority_queue<pair<double, ii> > q;

  for(int i=0; i<m; i++) {
    probabilities[i]= vector<double>(n);
    for (int j=0; j<n; j++)
      cin>> probabilities[i][j];
  }

  for(int i=0; i<m; i++) {
    int len; cin>> len;

    for(int k=0; k<len; k++) {
      int col; cin>> col;

      q.push(make_pair(probabilities[i][col],ii(-i,-m-col)));
    }
  }

  create(m+n);
  vector<ii> sol;

  while(!q.empty()) {
    ii edge=q.top().second; q.pop();
    edge.first=-edge.first; edge.second=-edge.second;
    if(find(edge.first)!= find(edge.second)) {
      sol.push_back(ii(edge.first, edge.second-m));
      unionn(edge.first, edge.second);
    }
  }

  sort(sol.begin(), sol.end());
  for(int i=0; i<sol.size(); i++){
    cout<<sol[i].first<<" "<<sol[i].second<<endl;
  }

  return 0;
}
