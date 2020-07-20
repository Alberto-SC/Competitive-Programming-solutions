#include <stdlib.h>
#include <iostream>
using namespace std;
int scarecrow(vector<char> field, tam){
	int cont,i=0,aux=0;
	while(field[i] != '\0'){
		if(field[i] == '.' || field[i] == '#'){
			if(field[i+1] == '.'){
				cont++;
				aux = i+1;
			}
		}
		i=aux++;
	}
	return cont;
}
int main(){
	int tam,i; 
	cin >> tam;
	vector<char> campito(tam);
	for(i=0; i<tam; i++){
		cin >> campito[i];
	}
	cout << "\nNo. de Scarecrows: %d",scarecrow(campito, tam);
} 
