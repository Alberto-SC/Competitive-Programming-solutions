#include <iostream>
#include <vector>
using namespace std;


vector<int> padre;
vector<int> h;
vector<int> numNodos;

int buscar(int u){
	if(padre[u]==u)return u;
	return padre[u] = buscar(padre[u]); 
}
void Union_find(int u, int v){
	u = buscar(u);
	v = buscar(v);
	if(u == v)	return;
	if(h[u]<h[v]){
		padre[u] = v;
		numNodos[v] +=numNodos[u];
	}
	else {
		padre[v] = u;
		numNodos[u] +=numNodos[v];
		h[u]+=h[v];
	}

}

int main(){
	ios_base::sync_with_stdio(0);
	std::ios::sync_with_stdio(0);
	int N,Q,u,v,p;
	char c;
	cin>> N>> Q;
	h.resize(N,1);
	numNodos.resize(N,1);
	for(int i = 0;i<N;i++){
		padre.push_back(i);
	}
	for(int i = 0;i<Q;i++){
		cin >>c;
		if(c == 'A'){
			cin>>u>>v;
			Union_find(--u,--v);
		}
		if(c == 'E'){
			cin >>p;
			cout<<numNodos[buscar(--p)]<<"\n";
		}
	}
	
	return 0;
}
