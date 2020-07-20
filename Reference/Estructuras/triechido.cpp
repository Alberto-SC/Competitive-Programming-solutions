#include <bits/stdc++.h>
using namespace std;
const int ALPH = 26;
//Struct trie Node whit array of childrens whit size of alphabet
struct trieNode{
    trieNode* child[ALPH];
    int prefix = 0; //count for number of words that a substring is prefix
    bool end; //mark if the node is a end of word
};

//init
trieNode* createNode(){
    trieNode* t= new trieNode;
    if(t){
        t->end=0;
        t->prefix=0;
        for(int i=0;i<ALPH;i++)
            t->child[i]=NULL;
    }
    return t;
}

void insert(trieNode* root,string key){
    trieNode* move = root;
    for(int i = 0;i<key.size();i++){
        int index = key[i]-'a';
        if(!move->child[index])
            move->child[index] = createNode();
        move = move->child[index];
        move->prefix++;
    }
    move->end = true;
}
int countprefixes(trieNode* root,string s){
    int n= s.size();
    trieNode* mov = root;
    for(int i=0;i<n;i++){
        int index = s[i]-'a';
        if(!mov->child[index])
             return 0;
        mov=mov->child[index];
    }
    return mov->prefix;
}
int search(trieNode* root ,string word){
    trieNode* S = root;
    for(int i = 0;i<word.size();i++){
        int index = word[i]-'a';
        if(!S->child[index])return 0;
        S = S->child[index];
    }
    return 1;
}
bool isEmpty(trieNode* root) { 
    for (int i = 0; i < ALPH; i++) 
        if(root->child[i]) 
            return false; 
    return true; 
} 
trieNode* remove(trieNode* root, string word, int depth = 0){ 
    if (!root) 
        return NULL; 
    if (depth == word.size()) { 
        if (root->end) 
            root->end = false;  
        if (isEmpty(root)) { 
            delete (root); 
            root = NULL; 
        } 
        return root; 
    } 
    int index = word[depth] - 'a'; 
    root->child[index] =  
          remove(root->child[index], word, depth + 1); 
    if (isEmpty(root) && root->end == false) { 
        delete (root); 
        root = NULL; 
    } 
    return root; 
} 

void print(trieNode* root, char str[], int level) { 
    if (root->end){ 
        str[level] = '\0'; 
        cout << str << endl; 
    } 
    int i; 
    for (i = 0; i < ALPH; i++)  { 
        if (root->child[i])  { 
            str[level] = i + 'a'; 
            print(root->child[i], str, level + 1); 
        } 
    } 
} 
int main(){
    int t,n;
    cin>>n;
    string dictionary[n];
    trieNode* root = createNode();
    for(int i = 0;i<n;i++){
        cin>>dictionary[i];
        insert(root,dictionary[i]);
    }  
    for(int i = 0;i<n;i++)
        cout<<countprefixes(root,dictionary[i])<<endl;
    cout<<search(root,dictionary[0])<<endl;
    char str[0];
    print(root,str,0);
    remove(root,dictionary[0]);
    cout<<endl;
    print(root,str,0);
}