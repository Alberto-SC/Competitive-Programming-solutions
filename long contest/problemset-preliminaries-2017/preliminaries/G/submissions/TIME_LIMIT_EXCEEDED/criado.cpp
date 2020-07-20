#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> ii;

// Slow solution using BFS instead of UFDS. Quadratic time.
bool connected(vector<vector<int>> g , int first, int second) {
  vector<bool> visited(g.size(),false);
  queue<int> q; q.push(first);

  while(!q.empty()) {
    int t=q.front(); q.pop(); visited[t]=true;
    if(t==second) return true;

    for(int v:g[t])
      if(!visited[v])
        q.push(v);
  }
  return false;
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

  vector<ii> sol;
  vector<vector<int>> g(n+m);

  while(!q.empty()) {
    ii edge=q.top().second; q.pop();
    edge.first=-edge.first; edge.second=-edge.second;

    if(!connected(g, edge.first, edge.second)) {
      g[edge.first].push_back(edge.second);
      g[edge.second].push_back(edge.first);
      sol.push_back(ii(edge.first, edge.second-m));
    }
  }

  sort(sol.begin(), sol.end());
  for(int i=0; i<sol.size(); i++){
    cout<<sol[i].first<<" "<<sol[i].second<<endl;
  }

  return 0;
}
