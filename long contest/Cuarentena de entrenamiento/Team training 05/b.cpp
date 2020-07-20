#include <bits/stdc++.h>
using namespace std;
int main(){
  int n;
  cin>>n;
  char grid[n][n];
  for(int i = 0;i<n;i++){
    for(int j = 0;j<n;j++){
      cin>>grid[i][j];
    }
  }
  bool flag = true;
  for(int i = 0;i<n;i++){
    int b = 0,w = 0;
    for(int j = 0;j<n;j++){
      if(grid[i][j] == 'B')b++;
      else w++;
    }
    if(b!=w)return cout<<0<<endl,0;
  }

  for(int i = 0;i<n;i++){
    int b = 0,w = 0;
    for(int j = 0;j<n;j++){
      if(grid[j][i] == 'B')b++;
      else w++;
    }
    if(b!=w)return cout<<0<<endl,0;
  }
  for(int i = 0;i<n;i++){
    int b=0,w=0;
    for(int j = 0;j<n;j++){
		if(grid[j][i] == 'B'){
			b++;
			w=0;
		}else{
			w++;
			b=0;
		}
        // cout<<b<<" "<<w<<endl;
		if(b>=3 || w>=3){
			return cout<<0<<endl,0;
		}
    }
  }
//   cout << "hola2"<< endl;
  for(int i = 0;i<n;i++){
   int b=0,w=0;
	// cout << "col=" << i << endl;
    for(int j = 0;j<n;j++){
		if(grid[j][i] == 'B'){
			b++;
			w=0;
		}else{
			w++;
			b=0;
		}
        // cout<<b<<" "<<w<<endl;
		if(b>=3 || w>=3){
			return cout<<0<<endl,0;
		}
    }
  }

  cout<<1<<endl;
  return 0;
}