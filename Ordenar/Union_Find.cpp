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
  	int padreA = raiz(0);
	for(i=1;i<=100;i++){
    	    if(raiz(i)!= padreA) {
			Nc++; 
    	    padreA = raiz(i);	
			}
    }
	}
  int Tamano(int u) {
    return tam[Raiz(u)];
  }
};









