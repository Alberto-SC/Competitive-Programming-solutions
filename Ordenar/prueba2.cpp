#include <iostream>
#include <vector>

using namespace std;
vector<int> a;
main(){
	int i;
	for(i = 0 ;i<10; i++){
		a.push_back(i*i+2);
		
	}
	for(int u:a){
		cout <<" \n"<< u;
	}
}
