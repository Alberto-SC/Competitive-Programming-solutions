#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


const int MAXN = 200020;
int NODOS = 0;
typedef int Costo;
const Costo INF = 1 << 30;
typedef pair<Costo, int> CostoNodo;
vector<CostoNodo> grafoCosto[MAXN];
const bool bi = true;

struct UnionFind {
  int n; 
  vector<int> padre, tam;
  
  
  UnionFind(int N) : n(N), tam(N, 1), padre(N) {
    while (--N) padre[N] = N;
  }
  int Raiz(int u) {
    if (padre[u] == u) return u;
    return padre[u] = Raiz(padre[u]);
  }
  bool SonConexos(int u, int v) {
    return Raiz(u) == Raiz(v);
  } 
  void Unir(int u, int v) {
    int Ru = Raiz(u); 
	int Rv = Raiz(v);
    if (Ru == Rv) return;
    --n, padre[Ru] = Rv;
    tam[Rv] += tam[Ru];
  }
  
  int NumC(){
  	int Nc = 1;
  	int padreA = Raiz(0);
	for(int i=1;i<=100;i++){
    	    if(Raiz(i)!= padreA) {
			Nc++; 
    	    padreA = Raiz(i);	
			}
    }
	}
  int Tamano(int u) {
    return tam[Raiz(u)];
  }
};


struct Ponderada{
  int x, y;
  Costo c;
  Ponderada(){}
  Ponderada(int x_, int y_, Costo c_) : x(x_), y(y_), c(c_) {}
  bool operator<(const Ponderada& q) const {
    return c < q.c;
  }
};
void AgregarArista(int u, int v, Costo c) {
  if (bi) grafoCosto[v].push_back(CostoNodo(c, u));
  grafoCosto[u].push_back(CostoNodo(c, v));
}

void limpia(){
  for( int i = 0; i < NODOS; i++ )
    grafoCosto[i].clear();
}

vector<Ponderada> Kruskal() {
	
  vector<Ponderada> todas;
  for (int u = 0; u < NODOS; ++u){
    for (CostoNodo arista : grafoCosto[u])
      todas.push_back(Ponderada(u, arista.second, arista.first) );
  }
  sort(todas.begin(), todas.end());
  vector<Ponderada> mst;
  UnionFind componentes(NODOS);
  for (Ponderada arista : todas) {
    int u = arista.x;
    int v = arista.y;
    if (!componentes.SonConexos(u, v))
     	 componentes.Unir(u, v), 
          mst.push_back(arista);
  }
  return mst;
}

int main(){
	int n,m,u,v,c;
	cin>>n>>m;
	NODOS = n;
	for(int i = 0;i<m;i++){
		cin>>u>>v>>c;
		AgregarArista(--u,--v,c);
	}
	vector<Ponderada> mst = Kruskal();
	
	for(int i = 0;i<mst.size();i++){
		cout<<"("<<mst[i].x+1<<","<<mst[i].y+1<<","<<mst[i].c<<") , ";
	}
	return 0;
	
}
