#include <bits/stdc++.h>
using namespace std;
#define MAX_CHAR 256 
struct SuffixTreeNode { 
    struct SuffixTreeNode *children[MAX_CHAR]; 
    struct SuffixTreeNode *suffixLink; 
    int start; 
    int *end; 
    int suffixIndex; 
};   
typedef struct SuffixTreeNode Node; 
string text;
Node *root = NULL; 
Node *lastNewNode = NULL; 
Node *activeNode = NULL; 
int activeEdge = -1,activeLength = 0,remaind = 0,leafEnd = -1; 
int *rootEnd = NULL; 
int *splitEnd = NULL; 
int size; 
  
Node *newNode(int start, int *end) { 
    Node *node =(Node*) malloc(sizeof(Node)); 
    int i; 
    for (i = 0; i < MAX_CHAR; i++) 
          node->children[i] = NULL; 
    node->suffixLink = root; 
    node->start = start; 
    node->end = end; 
    node->suffixIndex = -1; 
    return node; 
} 
  
int edgeLength(Node *n) { 
    return *(n->end) - (n->start) + 1; 
} 
  
int walkDown(Node *currNode) { 
    if (activeLength >= edgeLength(currNode)){ 
        activeEdge += edgeLength(currNode); 
        activeLength -= edgeLength(currNode); 
        activeNode = currNode; 
        return 1; 
    } 
    return 0; 
} 
void extendSuffixTree(int pos) { 
    leafEnd = pos; 
    remaind++; 
    lastNewNode = NULL; 
    while(remaind > 0) { 
        if (activeLength == 0) 
            activeEdge = pos;  
        if (activeNode->children[text[activeEdge]] == NULL){
            activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);
            if (lastNewNode != NULL){ 
                lastNewNode->suffixLink = activeNode; 
                lastNewNode = NULL; 
            } 
        } 
        else{ 
            Node *next = activeNode->children[text[activeEdge]];
                if (walkDown(next))
                    continue;
            if (text[next->start + activeLength] == text[pos]){ 
                if(lastNewNode != NULL && activeNode != root){ 
                    lastNewNode->suffixLink = activeNode; 
                    lastNewNode = NULL; 
                } 
                activeLength++; 
                break; 
            } 
            splitEnd = (int*) malloc(sizeof(int)); 
            *splitEnd = next->start + activeLength - 1; 
            Node *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;
            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;
            if (lastNewNode != NULL)  
                lastNewNode->suffixLink = split;   
            lastNewNode = split; 
        } 
        remaind--; 
        if (activeNode == root && activeLength > 0){ 
            activeLength--; 
            activeEdge = pos - remaind + 1; 
        } 
        else if (activeNode != root){
            activeNode = activeNode->suffixLink; 
        } 
    } 
} 
  
void print(int i, int j){ 
    int k; 
    for (k=i; k<=j; k++) 
        printf("%c", text[k]); 
} 
void setSuffixIndexByDFS(Node *n, int labelHeight){ 
    if (n == NULL)  return; 
    if (n->start != -1) 
        print(n->start, *(n->end));    
    int leaf = 1; 
    int i; 
    for (i = 0; i < MAX_CHAR; i++) { 
        if (n->children[i] != NULL) { 
            if (leaf == 1 && n->start != -1) 
                printf(" [%d]\n", n->suffixIndex); 
            leaf = 0; 
            setSuffixIndexByDFS(n->children[i], labelHeight + 
                                  edgeLength(n->children[i])); 
        } 
    } 
    if (leaf == 1){ 
        n->suffixIndex = size - labelHeight; 
        printf(" [%d]\n", n->suffixIndex); 
    } 
} 
  
void buildSuffixTree(){ 
    int i; 
    size = text.size(); 
    rootEnd = (int*) malloc(sizeof(int)); 
    *rootEnd = - 1; 
    root = newNode(-1, rootEnd); 
    activeNode = root; 
    for (i=0; i<size; i++) 
        extendSuffixTree(i); 
    int labelHeight = 0; 
    // setSuffixIndexByDFS(root, labelHeight); 
} 
int main(int argc, char *argv[]) { 
    clock_t begin = clock();
    cin>>text;
    //cout<<text<<endl;
    buildSuffixTree();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<fixed<<setprecision(15)<<time_spent<<endl;
    return 0; 
} 