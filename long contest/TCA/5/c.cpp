#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
typedef long long int lli;

int main(){
	int n; cin >> n;
	string brackets; cin >> brackets;
	vector<int> lvl(n);

	int h=0, mx = 0, inner = 0;
	for(int i=0; i<n; i++){
		if(brackets[i] == '[')
			h++;
		
		lvl[i] = h;
		mx = max(mx,h);
		
		if(brackets[i] == ']'){
			h--;
			if(brackets[i-1] == '[')
				inner++;
		}
	}

	for(int i=0; i<n; i++)
		cout << brackets[i] << " ";
	cout << endl;
	for(int i=0; i<n; i++)
		cout << lvl[i] << " ";
	cout << endl;

	map<int,int> height;
	h=1;
	int y = 0, x = (inner*5)+(n-inner);
	for(int i=mx; i>=1; i--){
		height[i] = h;
		y = h+2;
		h += 2;
	}

	for(auto p:height){
		cout << p.first << " " << p.second << endl;
	}

	int mid = y/2;
	cout << "y=" << y << ", mid=" << mid << endl;
	char draw[x][y];
	for(int i=0; i<y; i++){
		for(int j=0; j<x; j++){
			draw[i][j] = '.';
		}
	}

	//Print draw
	int dif,px=0,py;
	for(int k=0; k<n; k++){
		cout << "lvl=" <<  lvl[k] << endl;
		cout << "height=" <<  height[lvl[k]] << endl;
		dif = (height[lvl[k]]+2)/2;
		cout << "dif=" << dif << endl;

		cout << "(" << px << "," << mid-dif << ")" << endl;
		cout << "(" << px << "," << mid+dif << ")" << endl;
		draw[mid-dif][px] = '+';
		draw[mid+dif][px] = '+';
        px++;
	    for(int i=0; i<y; i++){
		    for(int j=0; j<x; j++){
			    cout << draw[i][j];
	    	}
		    cout << endl;
	    }
	}
	

	return 0;
}