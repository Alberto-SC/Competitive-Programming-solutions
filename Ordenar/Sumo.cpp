#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

typedef pair<int, int> Arista;
int NO = 1; 
const bool bi = true; 
vector< vector<int> > grafo; 
vector< vector<int> > NP; 
vector<int> color;
int MAX = 0,MAX2;

void AgregarArista(int u, int v,int i){
	if(bi)	grafo[v].push_back(u);
	grafo[u].push_back(v);
	NP[i].push_back(u);
	NP[i].push_back(v); 

}

BFS(int s){
	queue<int> q;
;
	q.push(s); 
	color[s] = 1;
	while( !q.empty() ){
		int u = q.front();
		q.pop();
		for(int v : grafo[u]){
			if(color[v] == -1) {
				color[v] = 1-color[u];
				 q.push(v);
			}
			else if(color[v] == color[u])
				color[v] =2;
		}		
	}	
}


int main(){
	int N,M,x,y;
    cin >> N; 
	cin>>M;
    grafo.resize(N);
    color.resize(N,-1);
    NP.resize(M);
    NO = N;
    for(  int i = 0; i < M; i++){
    	cin >> x >> y;
    	AgregarArista(--x, --y,i);
    }
    //for(int i = 0;i<M;i++)
    	//cout<<NP[i][0]<<","<<NP[i][1]<<"   ";
    BFS(5);
    for(int i = 0; i<N; i++){
    	cout<< "  "<<color[i];
	}
	return 0;
}
