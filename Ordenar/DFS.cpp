#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> Arista;

const int MAXN = 100020; 
int NODOS = 0; 
const bool bi = true; 
vector<int> grafo[MAXN]; 
int degree[MAXN]; 
int vis[MAXN];

void AgregarArista(int u, int v){
	if(bi){
		grafo[v].push_back(u);
		degree[v]++;
	}
	grafo[u].push_back(v); 
	degree[u]++;
}

void Limpia(){
	for( int i = 0; i < MAXN; i++ ){
		grafo[i].clear();
		degree[i] = 0;
	}
}


void DFS( int s ){
	vis[s] = 1;
	for( auto u : grafo[s] )
		if(vis[u] == -1)
			DFS(u);
}

int BFS( int s,int l){
	queue<int> q;
	int level = 1,p = 0,n,nl = 0,lr;
	q.push(s); vis[s] = 0;
	while( !q.empty() ){
		int u = q.front();
		q.pop();
		n = q.size()-nl;
		p++;
		for(int v : grafo[u]){
			if(vis[v] == -1) {
				vis[v] = vis[u]+1;
				 q.push(v);
				 nl++;
			}
		}
		if(n +p  == p){
			level++;
			nl = 0;
			p = 0;
		}
		if(level == l)
			return q.size();
			
		}
		return 0;
	}

void printListaAdj(int N){
	for(int i = 0; i<N;i++){
    	cout<<"\nNODO "<<i<<"->";
    	 for (vector<int>::iterator it = grafo[i].begin() ; it != grafo[i].end(); ++it)
    		cout << ' ' << *it;
    	
	}
}

int main(){
	int N, M, x, y,l;
    cin >> N;
    NODOS = N;
    for( int i = 0; i < N; i++ ) 
		vis[i] = -1;
    for(  int i = 0; i < N-1; i++){
    	cin >> x >> y;
    	AgregarArista(--x, --y);
    }
    cin>> l;
    if(l == 1)
    cout<<"1";
    else
    cout<< BFS(0,l);
    
	return 0;
}
