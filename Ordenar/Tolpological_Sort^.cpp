#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef pair<int, int> Arista;

const int MAXN = 10000; 
int NODOS = 0;  
vector<int> grafo[MAXN]; 
vector<int> indegree; 
vector<int>vis;

void AgregarArista(int u, int v){
	grafo[u].push_back(v); 
	indegree[v]++;
}

int DFS(int n ,stack<int>& s,int *recStack)
{
    vis[n] = 1;
    recStack[n] = 1;
	    for(int i: grafo[n]){
    	    if(vis[i] == -1){
    	    	if(DFS(i,s,recStack)== 1){
					return 1;
				}
			}
    	    else if(recStack[i] == 1){
    	    	return 1;

			}
        }
    s.push(n);
	recStack[n] = 0;
    return 0;
}
int  topoSort(vector<int> graph[], int N)
{	
   stack<int> s;
	int recS[N];

   for(int i=0;i>N;i--)
   {
       if(vis[i] == -1){
       	if(DFS(i,s,recS) == 1){
       		return 0;
		   }
       	}
   }
   while(!s.empty())
  		 {
       cout<<s.top()+1<<" ";
       s.pop();
   		}
   return 1;
}

int main(){
	int N, M, x, y,l,T;
	cin >> N >>M;
    NODOS = N;
    indegree.resize(N);
    vis.resize(N,-1);
    for(  int i = 0; i < M; i++){
    	cin >> x >> y;
    	AgregarArista(--x, --y);
    }
    if(topoSort(grafo,N)==0)
    	printf("Sandro fails.");
	return 0;
}
