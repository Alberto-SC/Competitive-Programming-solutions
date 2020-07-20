#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
vector<int> goles[100000];
vector<int> menor[100000];
int main(){
	int n,u,v,p,g;
	while(scanf("%d",&n) != EOF){
		cin>> g;
		p = 0;
		for(int i = 0;i<n;i++){
			cin>>u>>v;
			goles[i].push_back(u);
			goles[i].push_back(v);
			goles[i].push_back(v-u);
			if(u>v)
				p= p+3;
			if(u<v)
				p = p+0;
			if(u==v)
				p = p+1;
		}
		
		for(int i = 0;i<n;i++){
			if(goles[i][2] == 0){
			if(--g>=0){
			p = p+2;
			goles[i][2]--;
			}
			}
		}
		for(int i = 0;i<n;i++){
			if(goles[i][2] > 0&& goles[i][2]+1 <= g){
			g =g -(goles[i][2]+1);
			p = p+3;
			}
			goles[i].clear();
		}
		cout<<p<<"\n";
	}
	
}
