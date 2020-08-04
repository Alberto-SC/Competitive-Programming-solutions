#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

struct Trie{
    unordered_map<char, Trie*> child;
    int idx;
    bool end,used;
};
 
struct Trie *getNode(){
    struct Trie *p = new Trie;
    return p;
}

void insert(struct Trie* root, string key,int i){
    struct Trie *S = root;
    for(int i = 0;i<key.length();i++){
        if(S->child.find(key[i]) == S->child.end())
            S->child[key[i]] = getNode();
        S =  S->child[key[i]];
    }
    S->end = true;
    S->idx = i;
}

int search(struct Trie *root,string key){
    struct Trie* S = root;
    int n = key.size();
    for(int i = 0;i<n;i++){
        if(S->child.find(key[i]) == S->child.end())
            return -1;
        S = S->child[key[i]];
    }
    if(S->end){
        if(S->used)return -1;
        else {
            S->used = true;
            return S->idx;
        }
    }
    return -1;
}

int main(){
    int n,k,q;
    cin>>n>>k;
    vector<string> s(n);
    char c;
    for(int i = 0;i<n;i++){
        s[i] = string(k,'0');
        for(int j = 0;j<k;j++){ 
            cin>>c;
            s[i][j] = c;
        }
    }
    cin>>q;
    string t;
    Trie* root = getNode();
    for(int i = 0;i<q;i++){
        cin>>t;
        insert(root,t,i+1);
    }
    vector<int> ans(n);
    for(int i = 0;i<n;i++){
        // cout<<s[i]<<" ";
        int idx = search(root,s[i]);
        // cout<<idx<<endl;
        if(idx== -1)return cout<<"NO"<<endl,0;
        else ans[i] = idx;
    }
    cout<<"YES"<<endl;
    for(auto c:ans)cout<<c<<" ";
    cout<<endl;
    return 0;
}

