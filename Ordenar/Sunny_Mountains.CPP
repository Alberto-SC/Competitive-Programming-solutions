#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
using namespace std;

vector<pair<int,int>> puntos;

int main(){
	int n,x,y,t;
	cin>>t;
	double h ,H_RIGHT;
	for(int k = 0;k<t;k++){
	puntos.clear();
	cin>>n;
		for(int i = 0;i<n;i++){
			cin>>x>>y;
			puntos.push_back(make_pair(x,y));
		}
		sort(puntos.begin(), puntos.end());
		
		H_RIGHT = 0;
		h = 0;
	 	for (vector<pair<int,int>>::reverse_iterator prev = puntos.rbegin(), current = prev + 1; 
         	current != puntos.rend(); 
        	 current++, prev++) {
      		if (current->second > H_RIGHT) {
				double width_total = prev->first - current->first;
				double height_total = current->second - prev->second;
				double height_visible = current->second - H_RIGHT;
				double width_visible = width_total * height_visible / height_total;
				double hyp_visible = sqrt(height_visible * height_visible + width_visible * width_visible);
				h += hyp_visible;
				H_RIGHT = current->second;
      		}
    	}      
     printf("%.2f\n", h);
	}
	return 0;
}