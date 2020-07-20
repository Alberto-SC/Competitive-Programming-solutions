#include <iostream>
#include <map>
#include <math.h>
#include<vector>
using namespace std;
vector<pair<int,int>> grafo[100000];
void AgregarArista(int u ,int v,int c){
	grafo[u].push_back(make_pair(v,c));
	grafo[v].push_back(make_pair(u,c));
}
typedef struct Gp{
	int x,y,c
	Gp(){}
	Gp(int x_,int y_, int c_){x(x_),y(y_),c(c_)}
	bool operator<(const Ponderada& q) const {
    return c < q.c;
  }
};
int tsm(int  n){
	vector<Gp> aristas
	for(int i = 0;i<n;i++){
		for(auto a :grafo[i])
		aristas.push_back(i,a.first,a.second)
	}
	for(auto a :aristas){
		if(!sonConexos(a->x,a->y)){
			union_find(a->x,a->y);
			
		}	
	}
}
int main(){
	int n,x,y,c,u,v,costo,Cf = 0;
	pair<int,int> point ,pointu,pointv;
	map(int,pair<int,int>) m;
	while(cin>>n != EOF){
		c = 0;
		for(int i = 0; i<n;i++){
			cin >>x>>y;
			point = make_pair(x,y);	
				m[c] = pint;
				c++;
			cin>> q;
			for(int i = 0;i<q;i++){
				cin>>u>>v;
				pointv = m.find(v)->second
				pointu = m.find(u)->second
				costo =sqrt(pow(pointu->first-pointv->first,2)+pow(pointu->second-pointv->second,2))
				agregarArista(u,v,c);
				cf+= costo;
			}
			tsm(n);
		}
	}
	
	
	
}
