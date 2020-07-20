#include <bits/stdc++.h>

#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);

using namespace std;

typedef long long int lli;

int main(){
	string alphabet, word;
	cin >> alphabet >> word;

	set<string> ans;
	for(int i=0; i<=word.size(); i++){
		for(auto c:alphabet){
			//cout << "new ->" << word.substr(0,i) << " + " << c << " + " << word.substr(i,word.size()-i) << endl;
			string copy = word.substr(0,i) + c + word.substr(i,word.size()-i);
			ans.insert(copy);
		}
	}


	for(int i=0; i<word.size(); i++){
		string copy = word;
		for(auto c:alphabet){
			copy[i] = c;
			//cout << "copy -> " << copy << endl;
			ans.insert(copy);
		}
	}

	for(int i=0; i<word.size(); i++){
		//cout << "new ->" << word.substr(0,i) << " + " << word.substr(i+1,word.size()-i) << endl;
		string copy =  word.substr(0,i) + word.substr(i+1,word.size()-i);
		ans.insert(copy);
	}

	ans.erase(word);

	for(auto s:ans){
		cout << s << endl;
	}


	return 0;
}