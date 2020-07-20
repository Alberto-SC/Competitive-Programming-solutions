#include "template.hpp"

int lis(vector<int> &v){
	int n = v.size();
	vector<int> st(n+1,oo);
	vector<int> mx;

	st[0] = -oo;
	int last=0;

	FOR(i,n){
		if(v[i] > st[last]){
			st[++last] = v[i];

		}
		else{
			*lower_bound(st.begin(),st.end(),v[i]) = v[i];
		}
	}
	return last;
}

int main(){
	vector<int> v = {1,5,0,2,5,5,2,3,4};
	cout << "lis size = " << lis(v) << endl;
}
