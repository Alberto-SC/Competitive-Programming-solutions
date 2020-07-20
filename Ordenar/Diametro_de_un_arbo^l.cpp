#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

typedef pair<int, int> Arista;
int NO = 1; 
const bool bi = true; 
vector< vector<int> > grafo; 
int MAX = 0,MAX2;

void AgregarArista(int u, int v){
	if(bi)	grafo[v].push_back(u);
	grafo[u].push_back(v); 

}

pair<int,int> BFS( int s){
	queue<int> q;
	vector<int> dis(NO,-1);
	q.push(s); 
	dis[s] = 0;
	while( !q.empty() ){
		int u = q.front();
		q.pop();
		for(int v : grafo[u]){
			if(dis[v] == -1) {
				dis[v] = dis[u]+1;
				 q.push(v);
			}
		}		
	}

	int maxd= 0,in;
		for(int i = 0;i<NO;i++){
			if(dis[i]>maxd){
				maxd = dis[i];
				in = i;
			}

		}
	return make_pair(in,maxd);
	
}


int main(){
	int N,x,y;
    cin >> N;
    grafo.resize(N);
    NO = N;
    for(  int i = 0; i < N-1; i++){
    	cin >> x >> y;
    	AgregarArista(--x, --y);
    }
    cout<<BFS(BFS(0).first).second;
	return 0;
}
