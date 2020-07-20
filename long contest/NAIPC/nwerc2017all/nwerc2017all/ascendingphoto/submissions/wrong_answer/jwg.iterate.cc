#include <bits/stdc++.h>
using namespace std;

// NOTE this version starts at the front and eliminates pairs it comes accross. Fails on 7, 8, 9 at present.
// If you look at 9.jwg.in you'll see that it outputs 10, rather tha the correct 9. This is beacuse it doesn't
// take into account that 105 106 at the end don't need to be split, it marks 104 105 as used, and breaks
// a pair we could use. 

#ifdef DEBUG 
#define D_LOG(x) x
#else 
#define D_LOG(x)
#endif

struct Person {
	int height;
	int index;
	bool used = false;

	Person(int h) : height(h) {};
};

int main() {
	// Read in the information, eliminate consecutive dups.
	int last = 0,
	    height,
		i,
		n;

	cin>>n;
	vector<Person> heights;
	set<int> u_heights;

	for (i = 0; i < n; ++i) {
		cin>>height;
		if (height != last) {
			last = height;
			heights.push_back(Person(height));
			u_heights.insert(height);
		}
	}
	D_LOG(cout<<"input read in, after consecutive dups we have "<<heights.size()<<" values"<<endl;)
	D_LOG(cout<<u_heights.size()<<" unique values"<<endl;)

	// Identify what the order of the numbers should be We can do this by
	// sorting the unique numbers. Intead we keep a priority queue. insert uniue values in.
	for(auto it=heights.begin(); it<heights.end(); ++it) {
		it->index = distance(u_heights.begin(), u_heights.find(it->height));
		D_LOG(cout<<"(height: "<<it->height<<", index: "<<it->index<<")"<<endl;)
	}

	// Start off with N - 1 cuts.
	int cuts = n-1;

	// iterate over the (unsorted) list. 
	// 1. If two numbers are consecutive decrease the cuts. 
	// 2. Then look for other pairs the same and mark them as 'used up'.
	for(int i = 0; i < heights.size() - 1; ++i) {
		D_LOG(cout<<"i="<<heights[i].index<<", i+1="<<heights[i+1].index<<endl;)
		if (heights[i].used == true) {
			continue;
		}
		if (heights[i].index + 1 != heights[i+1].index) {
			continue;
		}
		// the two are consecutive. skip forward and look for copies that are NOT already used.
		bool found = false;
		for (int j = i + 2; j < heights.size() - 1; ++j) {
			if (heights[j].index == heights[i].index && heights[j].used == false &&
				heights[j+1].index == heights[i+1].index && heights[j+1].used == false) {
				D_LOG(cout<<"found a dup"<<endl;)
				found = true;
				heights[j].used = true;
				heights[j+1].used = true;
				j++;
			}
		}
		D_LOG(cout<<"cut--"<<endl;)
		cuts--;
		// if (!found) {
		// 	D_LOG(cout<<"cut--"<<endl;)
		// 	cuts--;
		// }

	}
	cout<<cuts<<endl;
}