#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int main(){
	list<char> cadena;
	list<char>::iterator it1,it2,it3;
	int x = 0;
	for(int i = 0;i<10;i++){
			cadena.push_back(i+65);
	}
	it1 = it2 = cadena.begin(); 
	it2 = ++it1;
	it1--;          
	cout<<"   "<<*it1 <<"   "<<*it2;
	cout<<"  "<<*it1;
  cout << "mylist contains:";
  for (it1=cadena.begin(); it1!=cadena.end(); ++it1)
  cout << ' ' << *it1;
  cout << '\n';
	return 0;
	
	}
