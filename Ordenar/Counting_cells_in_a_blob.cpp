#include <iostream>
#include <string>
using namespace std;
char grid[30][30];
int mx[] = { 1, 0, 1, -1, 0, -1, -1,1};
int my[] = { 0, 1, 1, 0, -1, -1, 1,-1};
bool vis[30][30];

int dfs(int x,int y,int c,int r){
	vis[y][x] = true;
	int sigx,sigy,tam=1;
	for(int i = 0;i<8;i++){
		sigx = x+mx[i];
		sigy = y+my[i];
		if(sigx>=0&& sigx<c && sigy<r && sigy>=0 && grid[sigy][sigx] =='1' &&!vis[sigy][sigx]){
		tam += dfs(sigx,sigy,c,r);
		}
	}
	return tam;
	
}
int main(){
	int T,r,c;
	cin>> T;
	string l;
	getchar();
	getchar();
	while(--T){
		for(int k = 0;k<30; k++){
			for(int l = 0;l<30;l++){
				vis[k][l] = false;
				grid[k][l] = '0';
			}
		}
		r = 0;c = 0;
		while(1){
			getline(cin, l);
			if(l.size() == 0)break;
			for(int a = 0;a<l.size();a++){
				grid[r][a] = l[a];
			}
			r++;
			c = l.size();
		}
		int NC = 0,n;
		for(int u = 0; u<r;u++){
			for(int v = 0;v<c;v++){
				if(!vis[u][v] && grid[u][v]=='1'){
					n= dfs(v,u,c,r);
					if(NC < n)NC = n;	 
				}
			}
		}
		cout << NC << endl;
		if(T);
		cout << endl;
	}
	
}
