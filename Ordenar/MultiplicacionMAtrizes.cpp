typedef vector<double> Vector;
typedef vector<Vector> Matriz;


Matriz MultiplicarMatriz(const Matriz &a, const Matriz &b){
	Matriz producto(a.size(), vector<double>(b[0].size(), 0.0000));
	for(int i = 0; i < a.size(); i++)
		for(int j = 0; j < b[0].size();j++)
			for(int k = 0; k < b.size(); k++)
				producto[i][j] += a[i][k]*b[k][j];
	return producto;
}


