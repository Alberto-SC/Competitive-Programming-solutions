#include <iostream>
#include <algorithm>
using namespace std;
int mx[] = { 1, 0,-1, 0};
int my[] = { 0, 1, 0, -1};
const int N = 1000,M = 1000;
int matriz[N][M];
int vis[N][M];
int dp[N][M];
int DP(int xo,int yo,int xf, int yf,int n,int m){
	cout<<"\n\n";
	for(int i = 0;i<n;i++){
		for(int j = 0;j<m;j++){
			cout<<dp[i][j]<<"  ";
		}
		cout<<"\n";
	}
	cout<<"\n\n";
	for(int i = 0;i<n;i++){
		for(int j = 0;j<m;j++){
			cout<<vis[i][j]<<"  ";
		}
		cout<<"\n";
	}
	if(xo ==xf && yo== yf){
		dp[yo][xo] = 0;
		return matriz[yo][xf];
	}
	for(int i = 0;i<4;i++){
		int x = xo+mx[i];
		int y = yo+my[i];
		if(x<0 || x== n || y<0 || y==m) {
		continue;
		}
		if(dp[y][x]!=1000){
		dp[yo][xo] =dp[y][x]+matriz[y][x];
		return dp[y][x];
		}
		if(matriz[y][x] != 1000&& vis[y][x] == -1){
		vis[y][x] = 1;	
		dp[yo][xo] = min(dp[yo][xo],DP(x,y,xf,yf,n,m)+matriz[y][x]);
		vis[y][x] = -1;
		}	
	}
		return dp[yo][xo];
}
int main(){
	int n,m,xo,yo,xf,yf;
	char c;
	cin>>n>>m;
	cin>>xo>>yo;
	cin>>xf>>yf;
	for(int i = 0;i<n;i++){
		for(int j = 0;j<m;j++){
			dp[i][j] =1000;
			cin>>c;
			vis[i][j] = -1;
			if(c == '#'){
			matriz[i][j] = 1000;
			}
			else if(c =='.'){
			matriz[i][j] = 1;}
			else
				matriz[i][j] = c-'0'+1;
		}
	}

	DP(--xo,--yo,--xf,--yf,n,m);
	cout<<dp[xo][yo];
	return 0;
}
