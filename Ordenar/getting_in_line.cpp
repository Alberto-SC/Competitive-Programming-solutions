#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <iomanip>
using namespace std;
typedef double COSTO;
typedef pair<COSTO,int> CostoArista;
vector<CostoArista> grafo[1000];
vector<int> outdegree(1000);
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
int union_find(int u, int v){
	if(outdegree[u]==2|| outdegree[v]== 2){
		return 0;
	}
	outdegree[u]++;
	outdegree[v]++;
	u = raiz(u);
	v = raiz(v);
	if(u == v)return 1;
	
	if(h[u]<h[v]) padre[u] = v;
	else if(h[u]>h[v]) padre[v] = u;
	else if(h[u] == h[v]){
		padre[u] = v;
		h[v]++;
	}
	
	return 1;
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

 double kruskal(int N,map<pair<int,int>,int> m){	
 	vector<Ponderado> Aristas;
 	double ct = 0.0;
 	for(int i = 0;i<N;i++)
 		for(CostoArista a: grafo[i])
 		Aristas.push_back(Ponderado(i,a.second,a.first));
 	
	sort(Aristas.begin(), Aristas.end());
	vector<Ponderado> mst;
	for(Ponderado a: Aristas){
		int u = a.x;
		int v = a.y;
		if(!SonConexos(u,v)){
			if(union_find(u,v)== 0){
				continue;
			}
			cout<<"Cable requirement to connect ("<< m[u] <<","<<m[v]<<") to ("<< m[u] <<","<<m[v]<<") is "<<a.c<<" feet";
			ct+= a.c;
			mst.push_back(a);
		}		
	}
	
	return ct;
}

int main(){
	int t,n = 0,u,v,key;
	vector<pair<int,int>> puntos;
	COSTO c;
	n = 1;
	map <pair<int,int>,int> m;
	pair<int,int> cp;
	while(n != 0){
		cin>>n;
		key = 0;
		padre.resize(n);
		for(int i = 0;i<n;i++){
			grafo[i].clear();
			padre[i] = i;
		}
		m.clear();
		h.resize(n,1);
		puntos.clear();
		for(int i = 0;i<n;i++){
			cin>>u>>v;
			puntos.push_back(make_pair(u,v));
			vector<pair<int,int>>::iterator it;
			it = puntos.end();
			--it;
			cp=*it;
			if(m.find(cp) == m.end()){
				m[cp] = key;
				key++;
			}
			for(int i = 0;i<puntos.size() ;i++){
				c  = sqrt(pow(cp.first-puntos[i].first,2)+pow(cp.second - puntos[i].second,2));	
				agregarArista(m[cp],m[puntos[i]],c);
			}
		}
			cout << std::fixed;
			cout << std::setprecision(2);
			if(n!= 0)
			cout<<kruskal(n)<<endl;
	}
	return 0;
}
