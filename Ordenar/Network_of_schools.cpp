#include <iostream>
#include <vector>
using namespace std;
vector<int> grafo[100];
int vis[100];
int r[100];
vector<int> g[100];
int indegree[100];
vector<int> outdegree(100,0);
int NV = 0;;

void  dfs(int i, int &t,int &min){
	vis[i] = 1;
	for(vector<int>::iterator it = grafo[i].begin() ; it != grafo[i].end(); ++it){
		if(vis[*it] == -1){
			dfs(*it,++t,min);
			t--;
		}
	}
	if(t <min)
		min = t;
}
int main(){
	int N,r=1,mina = 100,min = 100,c = 1,e =0;
	cin>> N;
	for(int i = 0;i<N;i++){
		while(r != 0){
		cin>> r;
		if(r != 0){
		grafo[i].push_back(--r);
		indegree[r]++;
		outdegree[i]++;
		vis[i] = -1;
		}	
		}
		r = 1;
	}
	for(int i = 0;i<N;i++){
		c = 1;
		for(int z = 0;z<N;z++){
			vis[z] == -1;
		}
		dfs(i,c,min);
		if(min <mina)
			mina = min;
	
	}
	for(int i = 0;i<N;i++){
		if(outdegree[i] == 0){
			e++;
		}
	}
	cout<<mina<<"\n"<<e;
	return 0;
}
