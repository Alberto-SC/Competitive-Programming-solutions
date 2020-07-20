#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef pair<int, int> Arista;

const int MAXN = 100020; 
int NODOS = 0; 
const bool bi = false; 
vector<int> grafo[MAXN]; 
int degree[MAXN]; 
vector<int>vis;

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




void DFS(int n ,stack<int>& s)
{
    vis[n] = 1;
    for(int i: grafo[n]){
        if(vis[i] == -1)
            DFS(i,s);
        }
    s.push(n);
}
int * topoSort(vector<int> graph[], int N)
{
   vis.resize(N,-1);
   stack<int> s;
   for(int i=0;i<N;i++)
   {
       if(vis[i] == -1)
       DFS(i,s);
   }
   cout<<"\n ";
   while(!s.empty())
  		 {
       cout<<s.top()<<" ";
       s.pop();
   		}

   
}

int main(){
	int N, M, x, y,l,T;
    cin >>T;
	cin >> M >>N;
    NODOS = N;
    for(  int i = 0; i < M; i++){
    	cin >> x >> y;
    	AgregarArista(x, y);
    }
    topoSort(grafo,N);
    
	return 0;
}
