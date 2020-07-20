#include <bits/stdc++.h>
using namespace std;

int main(){
  int n; cin>>n;
  vector<int> h(n); for (auto &i: h) cin>>i;

  vector<vector<int>> chunks;

  for (int i=0,j=1; i<h.size(); i=j++){
    while (j<h.size() and h[j-1]<h[j]) ++j;
    chunks.push_back(vector<int>(h.begin()+i,h.begin()+j));
  }

  priority_queue<pair<int,int>> todo;
  for (int i=0; i<chunks.size(); i++){
    todo.push({chunks[i].back(),i});
  }

  int res=0;
  for (int last=-1; not todo.empty();){
    int i=todo.top().second; todo.pop();
    int x=chunks[i].back(); chunks[i].pop_back();
    if (not chunks[i].empty()) todo.push({chunks[i].back(),i});
    res+=(last!=i and last!=-1);
    last=i;
  }

  cout<<res<<endl;
}
