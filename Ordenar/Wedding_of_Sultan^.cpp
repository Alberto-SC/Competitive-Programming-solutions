#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int main(){
	list<char> cadena;
	list<char>::iterator it,it1;
	int t,j;
	char c;
	int size;
	string s;
	vector<char> adjl[27];
	scanf("%d",&t);
	for(j = 0;j<t;j++){	
	getchar();	
	cin>>s;
	for(int i = 0;i<s.size();i++){	
		cadena.push_back(s[i]);
	}
	size = cadena.size();
 	it = cadena.begin();
 	while(!cadena.empty()){
 		it1 = ++it;
 		it--;
 		if(*it == *it1){
 			it = cadena.erase(it);
 			it = cadena.erase(it);
 			--it;
		 }
 		else{
		adjl[*it1-65].push_back(*it);
		adjl[*it-65].push_back(*it1);
		++it;
		 }
	}
	cout<<"Case "<<j+1<<"\n";
	for(int i = 0; i<27;i++){
			if(adjl[i].size()!= 0)
    		printf("%c = %d\n",i+65,adjl[i].size());
    		adjl[i].clear();
	}
	cadena.clear();
}	
	return 0;
}
