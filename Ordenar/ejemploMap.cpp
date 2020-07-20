#include <iostream>
#include <map>
#include <string>
using namespace std;
int main(){
	map <int,string> m;
	string a,b;
	int c = 0;
	for(int i = 0;i<3;i++){
		cin>>a>>b;
			m[c] =a;
			c++;
			m[c] =b;
			c++;
		
	}
	cout<<m.find(0)->second;

	}

