#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> grafo[200];
vector<int> color(200,-1);


void AgregarArista(int u, int v){
	int y= 0;
	if(grafo[u].size()>0){
	for(auto a:grafo[u]){
	if(a == v)
		y = 1;
	if(y == 0){
		grafo[u].push_back(v);

	}
	}
	}
	else{
		grafo[u].push_back(v);
	}
	y = 0;
	if(grafo[v].size()>0){
	for(auto a:grafo[v]){
		if(a== u)
			y = 1;
		if(y == 0)
			grafo[v].push_back(u);
	}
	}
	else{
			grafo[v].push_back(u);
	}
}
bool bipartite(int n){
	if(grafo[n].size()>0)
	color[n]= 1;
	else
	color[n]= -1;
	queue<int> q;
	q.push(n);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(auto a: grafo[u]){
			if(color[a]== -1){
				color[a] = 1-color[u];
				q.push(a);
			}
			else if(color[a] == color[u]){
				return false;
			}
		}
	}
	return true;
}
int main(){
	int M, N,NE,E;
	cin>>M;
	vector<int> R(M);
	bool t= true;
	for(int i = 0;i<M;i++){
		cin>> N;
		for(int j = 0;j<N;j++){
			cin>>NE;
			for(int k = 0;k<NE;k++){
				cin>> E;
				AgregarArista(j,--E);
			}
		}

	for(int x = 0;x<N;x++){
		if(color[x]== -1){
			if(!bipartite(x))
				t = false;
		}
	}
	if(t){
		int color1= 0,color2= 0,color3=0;
		for(int z = 0;z<N;z++){
			if(color[z] == 1)
				color1++;
			if(color[z] == 0)
				color2++;
			if(color[z] == -1)
				color3++;	 
		}
		if(color1<color2){
		R.push_back(color2+color3);
		}
		else
		R.push_back(color1+color3);
	}
	else
		R.push_back(0);
	for(int h = 0;h<N;h++){
		grafo[h].clear();
	}
	}
	for(auto d:R){
		cout<<d<<"\n";
	}
	return 0;
}
