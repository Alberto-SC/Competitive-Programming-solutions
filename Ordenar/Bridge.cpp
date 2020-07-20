#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;


int tiempo;
int NODOS;
typedef pair<int,int> Arista;
vector<int> grafo[100000];
vector<int> label, low;
vector<Arista> puentes; 
vector<bool> articulacion;
bool bi = true;
void agregarArista(int u, int v){
	if(bi)grafo[v].push_back(u);
	grafo[u].push_back(v);
} 


int PuentesArticulacion(int u, int p) {
  label[u] = low[u] = ++tiempo;
  int hijos = 0, retorno = 0;
  for (int v : grafo[u]) {
    if (v == p && !retorno++) continue;
    if (!label[v]) {
      ++hijos; PuentesArticulacion(v, u);
      if (label[u] <= low[v])
        articulacion[u] = true;
      if (label[u] <  low[v])
        puentes.push_back(Arista(u, v));
      low[u] = min(low[u], low[v]);
    }
    low[u] = min(low[u], label[v]);
  }
  return hijos;
}


void PuentesArticulacion() {
  low = vector<int>(NODOS);
  label = vector<int>(NODOS);
  tiempo = 0, puentes.clear();
  articulacion = vector<bool>(NODOS);
  for (int u = 0; u < NODOS; ++u)
    if (!label[u])
      articulacion[u] = PuentesArticulacion(u, NODOS) > 1;
}
int main(){
	int n,m,u,v;
	NODOS = n;
	cin>>n>>m;
	for(int i = 0;i<m;i++){
		cin>>u>>v;
		agregarArista(u,v); 
	}
	PuentesArticulacion();
	for(int i = 0;i<n;i++){
		cout<<articulacion[i]<<",";
	}
	cout<<endl;
	for(int i = 0;i<n;i++){
		cout<<"("<<puentes[i].first<<","<<puentes[i].second<<")";
	}
	return 0; 
}
