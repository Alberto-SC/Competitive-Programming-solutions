#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Person {
	int height;
	int position;
};


struct smallest_height {
	inline bool operator() (const Person& p1, const Person& p2) {
		return (p1.height < p2.height);
	}
};

int main(){
	int people; cin>>people;
	vector<Person> heights(people);

	int p = 0;
	for(auto &i: heights) {
		cin>>i.height;
		i.position = p++;
	}

	int cuts = 0;

	if ( people > 1) {
	    // Sort the array to be largest first.
		sort(heights.begin(), heights.end(), smallest_height());	

		for (int i = 1; i < people; ++i) {

			
			if (heights[i-1].position != heights[i].position - 1) {
				cuts++;
			}
		}
	}

	cout<<cuts<<'\n';
}