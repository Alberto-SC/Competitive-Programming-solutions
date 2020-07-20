#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h> 

using namespace std;
typedef int COSTO;
typedef pair<COSTO,int> CostoArista;
vector<CostoArista> grafo[2000];
vector<int> padre;
vector<int> h;
int origen;
vector<int> costosminimos;
vector<int> costos;
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

 int kruskal(int N,int o,int d,vector<int>costos ){	
 	vector<Ponderado> Aristas;
 	cout<<" Origen :"<<o<<"  \n";
 	
 	if(o == d){
 		auto result = std::minmax_element(costos.begin(),costos.end());
 		for(int i =0;i<costos.size();i++){
 			cout<<costos[i]<<",";
		 }
 		costosminimos.push_back(*result.second );
 		return 1;
	 }
 	if(origen == o){
 	for(CostoArista a: grafo[o])
 		Aristas.push_back(Ponderado(o,a.second,a.first));
	sort(Aristas.begin(), Aristas.end());
 	reverse(Aristas.begin(), Aristas.end());
	vector<Ponderado>::iterator it = Aristas.begin();
 	union_find(o,it->y);
 	costos.push_back(it->c);
	kruskal(N,it->y,d,costos);
	return 1;
	 }
	 else{
	 	for(CostoArista a: grafo[o])
 			Aristas.push_back(Ponderado(o,a.second,a.first));
 		sort(Aristas.begin(), Aristas.end());
 		reverse(Aristas.begin(), Aristas.end());
 		for(Ponderado a: Aristas){
 			if(!SonConexos(o,a.y)){
 			costos.push_back(a.c);
 			union_find(o,a.y);
			kruskal(N,a.y,d,costos);
			costos.pop_back();
			cout<<"\n";
			for(int i =0;i<costos.size();i++){
 			cout<<costos[i]<<",";
		 	}
			 }
			
		}
	 }
	
	return 1;
}

int main(){
	int t = 0,n=1,m=1,u,v,o,d,p;
	COSTO c;
	while(n!=0 && m!= 0){
		cin>>n>>m;
		padre.resize(n);
		h.resize(n,1);
		for(int i = 0;i<n ;i++){
			padre[i] = i;
			grafo[i].clear();
		}
		for(int i = 0; i<=m;i++){
			if(i<m){
			cin>>u>>v>>c;
			agregarArista(--u,--v,c);
			}
			if(i ==m){
				cin>>o>>d>>p;
			}
			
		}
		vector<int> costos;
		origen = --o;
		kruskal(n,o,--d,costos);
		if(n!=0 && m!= 0){
		auto result = minmax_element(costosminimos.begin(),costosminimos.end());
		cout<<"Scenario #"<<++t<<"\n"<<"Minimum Number of Trips = "<<ceil(p/(*result.second));
	}
	}
	return 0;
}
