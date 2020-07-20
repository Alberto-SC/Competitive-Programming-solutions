#include <bits/stdc++.h>
#define pb push_back
using namespace std;
string s;
int t;
int ans = 0;
struct Trie{
    unordered_map<char, Trie*> child;
    bool end;
};
 
struct Trie *getNode(){
    struct Trie *p = new Trie;
    return p;
}
 
void insert(struct Trie *root, string key){
    struct Trie *S = root;
    for(int i = 0 ; i < key.length(); i++){
        if(S->child.find(key[i]) == S->child.end())
            S->child[key[i]] = getNode();
 
        S = S->child[key[i]];
    }
    S-> end =true;
}
 
void calculateSubstrings(struct Trie *root){
    for(auto it = root->child.begin() ; it != root->child.end() ; it++){
        ans++;
        calculateSubstrings(it->second);
    }
}
bool search(struct Trie *root, string key){
    struct Trie *S = root;
    int n = key.size();
    for(int i = 0;i<n;i++){
        if(S->child.find(key[i]) == S->child.end())
            return false;
        S = S->child[key[i]];
    }
    if(S->end)return true;
    else 
        return false;
}
bool checkPreffix(struct Trie *root,string key){
    struct Trie* S = root;
    int n = key.size();
    for(int i = 0;i<n;i++){
       if(S->child.find(key[i]) == S->child.end())
            return false;
       S =S->child[key[i]];
    }    
    if(S->child.size()>0 || S->end)return true;
    else return false;
}
 
 
void print(Trie* root,char str[],int level){
    if(root->end){
        str[level] = '\0';
        cout<<str<<endl;
    }
    for(auto c:root->child){
        str[level] = c.first;
        print(c.second,str,level+1);
    }
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin >> t;
    Trie *root = getNode();
    while(t--){
        cin >> s;
        insert(root,s);
        // For calculate number of diferent substring substrings made a suffix trie
        // for(int i = 0 ; i < s.length() ; i++)
            // insert(root, s.substr(i));
        // ans = 0;
        // calculateSubstrings(root);
        // cout << ans << endl;
    }
    cout<<checkPreffix(root,"HOLA")<<endl;
    cout<<search(root,"HOLA")<<endl;
    cout<<search(root,"hola")<<endl;
}