#include <bits/stdc++.h>

#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);

using namespace std;

typedef long long int lli;

int main(){
	int r,c,a,b; cin >> r >> c >> a >> b;
	char mat[r][c];

	vector<int> A(a),B(b);
	for(auto &x:A) cin >> x;
	for(auto &x:B) cin >> x;

	int row=0,col=0;
	bool color=true;
	for(int i=0; i<a; i++){
		for(int m=0;m<A[i]; m++){
			color = (i%2)?false:true;
			col=0;

			for(int j=0; j<b; j++){
				for(int n=0; n<B[j]; n++){
 					mat[row+m][col+n] = color?'B':'W';
				}
				col += B[j];
				color = !color;
			}
		}
		row += A[i];
	}

	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			cout << mat[i][j];
		}
		cout << endl;
	}



	return 0;
}