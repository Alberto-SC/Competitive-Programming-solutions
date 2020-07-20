#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef int COSTO;
typedef pair<COSTO,int> CostoArista;
vector<CostoArista> grafo[2000];
vector<int> padre;
vector<int> h;

void agregarArista(int u, int v,COSTO c){
	grafo[u].push_back(CostoArista(c,v));
	grafo[v].push_back(CostoArista(c,u));
}

int raiz(int u){
	if(padre[u]== u)return u;
	return padre[u] = raiz(padre[u]);
}
void union_find(int u, int v){
	u = raiz(u);
	v = raiz(v);
	if(u == v)return;
	
	if(h[u]<h[v]) padre[u] = v;
	else if(h[u]>h[v]) padre[v] = u;
	else if(h[u] == h[v]){
		padre[u] = v;
		h[v]++;
	}
}
bool SonConexos(int u, int v) {
    return raiz(u) == raiz(v);
  } 

struct Ponderado{
	int x ;
	int y;
	COSTO c ;
	Ponderado(){}
  	Ponderado(int x_, int y_, COSTO c_) : x(x_), y(y_), c(c_) {}
  	bool operator<(const Ponderado& q) const {
    return c < q.c;
  	}
};

 int kruskal(int N){	
 	vector<Ponderado> Aristas;
 	int ct = 0;
 	for(int i = 0;i<N;i++)
 		for(CostoArista a: grafo[i])
 		Aristas.push_back(Ponderado(i,a.second,a.first));
 	
	sort(Aristas.begin(), Aristas.end());
	vector<Ponderado> mst;
	for(Ponderado a: Aristas){
		int u = a.x;
		int v = a.y;
		if(!SonConexos(u,v)){
			union_find(u,v);
			ct+= a.c;
			mst.push_back(a);
		}		
	}
	
	return ct;
}

int main(){
	int t,n,m,key;
	string u,v;
	COSTO c;
	map<string,int> ma;
	cin>>t;
	getchar();
	for(int a = 0;a<t;a++){
		cin>>n>>m;
		padre.resize(n);
		h.resize(n,1);
		for(int i = 0;i<n ;i++){
			padre[i] = i;
			grafo[i].clear();
		}
		ma.clear();
		key = 0;
		for(int i = 0; i<m;i++){
			cin>>u>>v;
			if(ma.find(u)== ma.end()){
				ma[u] = key;
				key++;
			}
			if(ma.find(v) == ma.end()){
				ma[v] = key;
				key++;
			}
			cin>>c;
			agregarArista(ma[u],ma[v],c);
		}
		cout<<kruskal(n);
		if(a < t-1)
		cout<<"\n\n";
	}
	return 0;
}
