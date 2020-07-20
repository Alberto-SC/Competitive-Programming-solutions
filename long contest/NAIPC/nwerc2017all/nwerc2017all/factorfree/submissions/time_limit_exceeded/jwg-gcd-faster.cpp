#include <iostream>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

unsigned int *nodes;
unsigned int *answer;

bool find_tree(int left, int right, int parent_idx) {
	//cout<<"left="<<left<<", right="<<right<<", parent_idx="<<parent_idx<<"\n";
	if (right - left == 0) {
		return true;
	}
	if (right - left == 1) {
		answer[left] = parent_idx;
		return true;
	}
	bool not_coprime[right-left] {false};
	bool all_coprime;
	unsigned int g;
	unsigned int node_i, node_j;
	for(int i=left; i < right; ++i) {
		node_i = nodes[i];
		if (not_coprime[i-left]) {
			continue;
		}
		all_coprime = true;
		
		for(int j = left; j<right; ++j) {
			
			//cout<<"gcd="<<g<<", nodes[" << i << "]="<<nodes[i]<<", nodes[" << j << "]="<<nodes[j]<<"\n";
			if (j == i) {
				continue;
			}
			node_j = nodes[j];
			if (node_j == node_i) {
				all_coprime = false;
				not_coprime[j-left] = true;
				break;
			}
		    g = std::__gcd(node_j, node_i);
			if (g != 1) {
				all_coprime = false;
				not_coprime[j-left] = true;
				break;
			}
		}
		if(all_coprime) {
			answer[i] = parent_idx;
			return find_tree(left, i, i) and find_tree(i+1, right, i);
		}
	}
	return false;
}

int main() {
	// read in all of the numbers.
    int n; cin>>n;

    nodes = new unsigned int[n];
    answer = new unsigned int[n];

    for(int i = 0; i < n; ++i) {
    	cin>>nodes[i];
    	//cout<<nodes[i]<<" ";
    }
    //cout<<"\n";
    if(find_tree(0, n, -1)) {
	    for (int i=0; i<n; i++){
	      cout<<answer[i]+1<<(i+1==n? '\n': ' ');
	    }
    } else {
    	cout<<"impossible"<<endl;
    }
}
