#include<bits/stdc++.h>

using namespace std;

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

	int N,K;
	string nomb,aux,ofnomb;
	bool pea,pan,find=false;
	cin>>N;
	for(int i=0; i<N; i++){
		cin>>K;
		cin.ignore();
		getline(cin,nomb);
		pea=false;

		pan=false;
		for(int j=0; j<K;j++){
			getline(cin,aux);
			if(aux=="pea soup") pea=true;
			if(aux=="pancakes") pan=true;
		}
		if(pea and pan and !find){
			ofnomb=nomb;
      find=true;;
		}
	}
  if(find) cout<<ofnomb<<"\n";
	else cout<<"Anywhere is fine I guess\n";
	return 0;
}