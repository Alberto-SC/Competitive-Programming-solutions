#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> NumN(54*20,1);
int padre[54*20];
vector<int> h(54*20);
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
	int t,n,a = 0,b=0;
	string u,v;
	cin>> t;
	for(int i = 0;i<t;i++){
		cin>> n;
		for(int k = 0;k<54*20;k++){
			padre[k] = k;
			NumN[k] = 1;
		}
		for(int j = 0;j<n;j++){
			cin>> u>>v;
			for(int x = 0;x<(u.size()<v.size()? v.size():u.size());x++){
				if(u[x]!='\0')
					a = a+u[x];
				if(v[x]!='\0')
					b = b+v[x];
			}
			
			union_(a-65,b-65);
			cout<<NumN[raiz(a-65)]<<"\n";
		}
		
	}
	return 0;
}
