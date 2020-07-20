#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> grafo[100000];
vector<int> water;
void AgregarArista(int u,int v){
			grafo[u].push_back(v);
			grafo[v].push_back(u);
}
void printListaAdj(int N){
	for(int i = 0; i<N;i++){
    	cout<<"\nNODO "<<i<<"->";
    	 for (vector<int>::iterator it = grafo[i].begin() ; it != grafo[i].end(); ++it)
    		cout << ' ' << *it;
    	
	}
}
int main(){
	int R,C,M,N,W,T,d,b,even = 0,odd = 0,y=0,x=0;
	cin>> T;
	pair<int,int> actual;
	for(int i = 0;i<T;i++){
		cin>>R>>C>>M>>N;
		bool visitado[R*C];
		cin>> W;
		int direction[8][2] = {
            {M, N}, {-M, N}, {M, -N}, {-M, -N},
            {N, M}, {-N, M}, {N, -M}, {-N, -M}
        };
		water.resize(R*C); 
		for(int j = 0;j<W;j++){
			cin>>d>>b;
			water[b+(C*d)] = 1;
		}
		queue<pair<int,int>> q;
	    q.push(make_pair(0, 0));
	    visitado[0]= true;
		while(!q.empty()){
			actual = q.front();
			q.pop();
				for(int j = 0;j<8;j++){
				x = actual.first+direction[j][0];
				y = actual.second+direction[j][1];
				if(x >= 0 && x < R && y >= 0 && y < C && water[y+(C*x)]== 0){
					grafo[actual.second+(C*actual.first)].push_back(y+(C*x));
					if(!visitado[y+(C*x)]){
						visitado[y+(C*x)] = true;
						q.push(make_pair(x,y));
					}
				}
				}
		}
		for(int z = 0;z<R*C;z++){
			if(grafo[z].size()==0)continue;
			
			if(grafo[z].size()%2 ==1|| grafo[z].size()==1){
				odd++;
				grafo[z].clear();
			}else {
				even++;
				grafo[z].clear();
			}
		}
		if(odd == 0&& even == 0)even = 1;
		cout<<"case "<<i+1<<": "<<even<<" "<<odd<<"\n";
		even = odd = 0;
		water.clear();
		for(int z = 0;z<R*C;z++)
			visitado[z]= false;

	}
}
