#include <bits/stdc++.h>
#define print(A)for(auto c:A)cout<<c<<" \n"[c==*(A.end())-1];
using namespace std;

vector<int> h(30,1);
vector<int> padre(30);
vector<pair<char,char>> cambios;
map<int,char> m;
int raiz(int u){
	if(padre[u] == u) return u;
	else return padre[u] = raiz(padre[u]);
		
}
bool conexos(int u, int v){
	if(raiz(u) == raiz(v))return true;
	else return false;
}
void Union_find(int u, int v){
	u = raiz(u);
	v = raiz(v);
	if(conexos(u,v))return;
	if(h[u]<h[v])padre[u] = v;
	else{	
		padre[v]= u;
		if(h[u] == h[v]] ++ h[u];
	}
}

int solution(string s1,string s2){
	int c = 0;
	print(padre)
	for(int i = 0;i<s1.size();i++){
		if(s1[i] == s2[i])continue;
		else if(conexos(s1[i]-'a',s2[i]-'a')) continue;
		else{
			Union_find(s1[i]-'a',s2[i]-'a');
			cambios.push_back(make_pair(s1[i],s2[i]));
			c++;
		}
	}
	return c;
}



int main(){
	int l,cont = 0;
	cin>>l;
	int N = 30;
	while(--N) padre[N] = N;
	char c;
	string s1;
	string s2;
	cin>>s1>>s2;
	cout<<solution(s1,s2)<<endl;
	for(int i = 0;i<cambios.size();i++){
		cout<<cambios[i].first<<" "<<cambios[i].second<<"\n";
	}
	return 0;
}