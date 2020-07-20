#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
vector<int> NumN(200000,1);
int padre[200000];
vector<int> h(200000);
int raiz(int u){
	if(padre[u]== u)return u;
	return padre[u] = raiz(padre[u]);
}

int union_(int u ,int v){
	u = raiz(u);
	v = raiz(v);
	if(u == v)return 0;
	if( h[u]<h[v] ){
	padre[u] = v;
	NumN[v]= NumN[v]+NumN[u];
	}
	else if(h[v]<h[u]){
	padre[v] = u;
	NumN[u]= NumN[u]+NumN[v];	
	}
	else if(h[u] == h[v]){
		padre[v] = u;
		h[u]++;
		NumN[u]= NumN[v]+NumN[u];
	}
	return 1;
}
int main(){
	int t,n,c = 0;
	map<string,int> m;
	string u,v;
	cin>> t;
	for(int i = 0;i<t;i++){
		cin>> n;
		for(int k = 0;k<200000;k++){
			padre[k] = k;
			NumN[k] = 1;
		}
		for(int j = 0;j<n;j++){
			cin>> u>>v;
			if(m.find(u)== m.end()){
				m[u] = c;
				c++;
			}
			if(m.find(v) == m.end()){
				m[v] = c;
				c++;
			}
			
			union_(m[u],m[v]);
			cout<<NumN[raiz(m[u])]<<endl;
		}		
		
	}
		
	return 0;
}
