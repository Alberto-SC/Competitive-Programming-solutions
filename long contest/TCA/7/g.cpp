#include <bits/stdc++.h>
using namespace std;
struct Trie{
    Trie* childs[2];
    int value,count;
    bool end;
};

Trie* createNode(){
    Trie* T = new Trie;
    T->childs[0]  = T->childs[1] = NULL;
    T->value =0;
    T->end = false;
    T->count = 0;
    return T;
}

void insert(Trie *root,int val){
    Trie *S = root;
    for(int i = 31;i>=0;i--){
        bool b = (val>>i)&1;
        if(S->childs[b] == NULL){
            S->childs[b] = createNode();
        }
        S = S->childs[b];
    }
    S-> value = val;
    S-> count++;
    S-> end = true;
}
int searchMaxXOR(Trie* root, int val){
    Trie *S = root;
    int maximo = 0;
    for(int i = 31 ;i>=0;i--){
        bool b = (val>>i)&1;
        if(S->childs[1-b]!= NULL)S = S->childs[1-b];
        else if (S->childs[b] != NULL) S =  S->childs[b];
    }
    return val^S->value;
}

bool check(Trie* node){
    if(node->childs[0]== NULL && node->childs[1] == NULL)return true;
    return false;
}
Trie* remove(Trie* root, int key, int depth = 31){
    if(!root)
        return NULL;
    if (depth ==-1) {
        if(root->count== 1){
            root->end = false;
            delete (root);
            root = NULL;
        }
        else root->count--;
        return root;
    }
    int idx = (key>>depth)&1;
    // cout<<idx<<endl;
    root->childs[idx] =  remove(root->childs[idx], key, depth - 1);
    if (check(root) && root->end == false) {
        delete(root);
        root=NULL;
    }
    return root;
}

void print(Trie* root){
    if(root->end){
        cout<<root->value<<" "<<root->count<<endl;
        return;
    }
    if(root->childs[0]!= NULL)
        print(root->childs[0]);
    if(root->childs[1]!= NULL)
        print(root->childs[1]);
}

int main(){
    int t,n,x;
    cin>>t;
    char c;
    Trie* root = createNode();
    insert(root,0);
    while(t--){
        cin>>c;
        cin>>x;
        if(c == '?'){
            cout<<searchMaxXOR(root,x)<<endl;
        }
        else if(c == '+'){
            insert(root,x);
        }
        else{
            remove(root,x);
            // print(root);
        }
    }
    return 0;
}