#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000;
#define print(A) for(auto c :A)cout<<c<<" ";
//________________DINAMIC SEGMENT TREE___________________//
typedef long long ll;
struct Node {
    ll sum;
    Node *l, *r;
    Node() : sum(0), l(NULL), r(NULL) { }
};
void add(Node *v, int l, int r, int q_l, int q_r, ll val) {
    if (l > r || q_r < l || q_l > r)
        return;
    if (q_l <= l && r <= q_r) {
        v -> sum += val;
        return;
    }
    int mid = (l + r) >> 1;
    if (v -> l == NULL)
        v -> l = new Node();
    if (v -> r == NULL)
        v -> r = new Node();
    add(v -> l, l, mid, q_l, q_r, val);
    add(v -> r, mid + 1, r, q_l, q_r, val);
}

ll get(Node *v, int l, int r, int pos) {
    if (!v || l > r || pos < l || pos > r)
        return 0;
    if (l == r) 
        return v -> sum;
    int mid = (l + r) >> 1;
    return v -> sum + get(v -> l, l, mid, pos) + get(v -> r, mid + 1, r, pos);
}

int n, m, t, x, y, val;
char c;




//__________________SEGMENT TREE_______________//
/*
    Simple segment tree
*/
// vector<int> st(4*MAXN);
// void build(vector<int> &A,int v,int SL,int SR){
//     if(SL == SR)
//         st[v] = A[SL];
//     else{
//         int SM = (SL+SR)/2;
//         build(A,v*2,SL,SM);
//         build(A,v*2+1,SM+1,SR);
//         st[v]= st[v*2]*st[v*2+1];
//     }
// } 
// int query(int v, int SL,int SR,int l,int r){
//     if(l>r)
//         return 1;
//     if(SL == l && SR == r)
//         return st[v];
//     int SM = (SL + SR) / 2;
//     return query(v*2,SL,SM,l,min(SM,r)) * query(v*2+1,SM+1,SR,max(l,SM+1),r);
// }
// void update(int v,int SL,int SR,int pos,char new_v){
//     if(SL == SR)
//         st[v]=new_v;
//      else{
//         int SM = (SL+SR)/2;
//         if(pos<=SM)
//             update(v*2,SL,SM,pos,new_v);
//         else
//             update(v*2+1,SM+1,SR,pos,new_v);
//         st[v] = st[v*2]*st[v*2+1]; 
//     }
        
// }
/*
    Segment tree Lazy Propagation
*/
void propagate_product(int v ,int SL, int SR){
    if(lazyP[v] == 1)return ;
    st[v] =(1ll* st[v]* mod_pow(lazyP[v],(SR-SL+1)))%mod;
    if(SL!=SR){
        lazyP[v*2] =(1ll*lazyP[v*2]*lazyP[v])%mod;
        lazyP[v*2+1] =(1ll*lazyP[v*2+1]*lazyP[v])%mod;
    }
    lazyP[v] = 1;
}
void Update_product(int v, int SL, int SR, int L, int R, int mult){ 
    propagate_product(v,SL,SR);
    if(SL>SR || SR<L || R<SL)return;
    if(L<=SL && SR<=R){
        lazyP[v] =(1ll * lazyP[v]*mult)%mod;
        propagate_product(v,SL,SR);
        return;
    }
    int SM = (SL+SR)/2;
    Update_product(v*2,SL,SM,L,R,mult);
    Update_product(v*2+1,SM+1,SR,L,R,mult);
    st[v] = (1ll*st[v*2]*st[v*2+1])%mod;
}

lli query_product(int v,int SL,int SR,int L,int R){
    propagate_product(v,SL,SR);
    if(SL>SR || SR<L || R<SL)return 1;
    if(L<=SL && SR<=R)return st[v];
    int SM = (SL+SR)/2;
    lli p1 = query_product(v*2,SL,SM,L,R);
    lli p2 = query_product(v*2+1,SM+1,SR,L,R);
    return (p1*p2)%mod;
}


//_____________________TRIE_________________________//
const int SIZE = 10; 
struct TrieNode { 
	struct TrieNode *children[SIZE]; 
	bool isEndOfWord; 
}; 

struct TrieNode *getNode(void) { 
	struct TrieNode *pNode = new TrieNode; 
	pNode->isEndOfWord = false; 
	for (int i = 0; i < SIZE; i++) 
		pNode->children[i] = NULL; 
	return pNode; 
} 

void insert(struct TrieNode *root, string key) { 
	struct TrieNode *pCrawl = root; 
	for (int i = 0; i < key.length(); i++) { 
		int index = key[i] - '0'; 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 
		pCrawl = pCrawl->children[index]; 
	}  
	pCrawl->isEndOfWord = true; 
} 

int  search(struct TrieNode *root, string key) { 
	struct TrieNode *pCrawl = root; 
	for (int i = 0; i < key.length(); i++) { 
		int index = key[i] - '0'; 
		if (!pCrawl->children[index]) {
			return false; 
            cout<<"HOLA"<<endl;
        }
		pCrawl = pCrawl->children[index]; 
	}
    int cont = 0;
    return cont;
} 

int main() {
    /*
        Test Dinamic Segment tree
    */
    // int n,x,m,c;
    // Node *root = new Node();
    // scin>>n;
    // for (int i = 0; i < n; i++) {
    //     cin>>x;
    //     add(root, 0, n-1, i, i, x);
    // }
    // cin>>m;
    // for (int i = 0; i < m; i++) {
    //     cin>>c;
    //     if (c == 'a') {
    //         scanf("%d%d%d", &x, &y, &val);
    //         add(root, 0, n - 1, --x, --y, val);
    //     } else {
    //         scanf("%d", &x);
    //         printf("%I64d ", get(root, 0, n - 1, --x));
    //     }
    // }
/*
    Test segment tree
*/
    // int n;
    // vector<int>nums(n);
    // for(int i = 0;i<n;i++)
    //     cin>>nums[i];
    // build(a,1,0,5);
    // print(t);
    // cout<<endl<<query(1,0,5,2,4);
/*
    TEST Segment tree Lazy
*/
    int n;
    cin>>n;
    vector<int>nums(n);
    for(auto &X:nums)cin>>X;
    build(nums,1,0,n-1);
    int upd;
    cin>>upd;
    for(int i = 0;i<4*n;i++)
        cout<<st[i]<<" ";
    cout<<endl;
    cout<<endl<<query(1,0,n-1,2,4)<<endl;
    update(1,0,n-1,2,4,upd);
    for(int i = 0;i<4*n;i++)
        cout<<st[i]<<" ";
    cout<<endl;
    cout<<endl<<get(1,0,n-1,0)<<endl;
/*
    Test  trie
*/
}