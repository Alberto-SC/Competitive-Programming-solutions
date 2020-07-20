#include <iostream>
#include <vector>
#include <algorithm>
#define int COSTO;

struct ponderado{
	int u,v;
	COSTO c;
	ponderado(){}
	pomderado(int _u,int _v, COSTO _c):u(_u),v(_v),c(_c);
};
vector<vector<pair<COSTO,int>> grafo;
vector<int> padre;
vector<int> h;
void Agregar_arista(int u,int v, COSTO c){
	grafo[u].push_bacK(make_pair(v,c)):
}
int raiz(int u ){
	if(padre[u] == u)return u 
	return padre[u] = raiz(u);
}
union_find(int u ,int v){
	u = raiz(u);
	v = raiz(v);
}
bool Conexos(int u ,int v){
	if(raiz(u) == raiz(v))return true;
	return false;
}
int mast(int n ){
	int cont = 0;
	vector<ponderado> mst;
	for (int u = 0; u < n; ++u){
    	for (CostoNodo arista : grafoCosto[u])
     		 mst.push_back(Ponderada(u, arista.second, arista.first) );
  }
	sort(mst.begin(), mst.end( ), [ ]( const vector<ponderado>& lhs, const vector<ponderado>& rhs ){	
   			return lhs.c < rhs.c;
		});
	for(int i = 1;i<mst.size();i++){
		int u = mst[i].u;
		int v = mst[i].v;
		if(!Conexos&& mst[i].c>mst[i-1].c){
			cont++;
			union_find(mst[i].u,mst[i].v);

		}
	}
	return cont;
}
int main(){
	int n,m,u,v;
	COSTO c;
	cin>> n>>m;
	grado.rezise(n);
	padre.rezise(n);
	h.rezise(n);
	int N = n;
	while(--N) padre[N] = N;
	
	for(int i = 0;i<m;i++){
		cin>>u>>v>>c;
		Agregar_arista(u,v,c);
	}
	mast(n);
	return 0;

}