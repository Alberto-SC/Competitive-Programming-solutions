/* 
	init: p[i][j] = i ; d[V][V];
	for(0, V, i): for(0, V, j): for(0, V, k):
		if d[i][k]+p[k][j] < d[i][j]:
			p[i][j] = p[k][j]
			d[i][j] = d[i][k] + d[k][j]
*/
         
         
void show( int from, int to ){
	if( from != to ){
		show( from, p[from][to] );
		cout << " ";
	}
	cout << to;
}
