#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
// #define int long long 
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
#define cerr(s) cerr << "\033[48;5;203m\033[38;5;15m" << s << "\033[0m"
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> dis(numeric_limits<int>::min(), numeric_limits<int>::max());

// Implicit Treap 
// All operation complexity is O(nlogn)
// Supports a dinamic array with operations:
// insert/erase at every position
// Range sum/minimum/max 
// reverse/rotate Sub array

struct Treap{
    Treap *l  = NULL,*r = NULL;
    int p,sz = 1,val,sum = 0,mn = 1e9;
    int rev = 0, lazySum  = 0,lazyReplace = 0;
    int sumPend  = 0,ReplacePend = 0;
    Treap(int v ,int prior = dis(rng)):val(v),p(prior){}
};
Treap *root = NULL;

void update(Treap *T){
    if (!T) return;
    T->sz = 1;
    T->sum = T->val;
    T->mn = T->val;    
    if (T->l) {
      T->sz += T->l->sz;
      T->sum += T->l->sum;
      T->mn = min(T->mn,T->l->mn);
    }
    if (T->r) {
      T->sz += T->r->sz;
      T->sum += T->r->sum;
      T->mn = min(T->mn,T->r->mn);
    }
}

void applyRev(Treap *T){
    if(!T)return;
    T->rev^=1;
    swap(T->l,T->r);
}

void applySum(Treap *T,int x){
    if(!T)return;
    T->val+=x;
    T->mn+=x;
    T->sumPend+=x;
    T->lazySum = 1;
    T->sum+=x*T->sz;

}
void applyReplace(Treap *T,int x){
    if(!T)return;
    T->val=x;
    T->mn=x;
    T->ReplacePend=x;
    T->lazyReplace = 1;
    T->sum=x*T->sz;
}
void lazy(Treap *T){
    if(!T)return;
    if(T->rev){
        applyRev(T->l);
        applyRev(T->r);
        T->rev = 0;
    }
    if(T->lazySum){
        applySum(T->l,T->sumPend);
        applySum(T->r,T->sumPend);
        T->lazySum = 0;
        T->sumPend = 0;
    }
    if(T->lazyReplace){
        applyReplace(T->l,T->ReplacePend);
        applyReplace(T->r,T->ReplacePend);
        T->lazyReplace = 0;
        T->ReplacePend = 0;
    }
}
pair<Treap*,Treap*> split(Treap *T,int idx,int cont = 0){
    if(!T)return {NULL,NULL};
    lazy(T);
    Treap *L, *R;
    int idxt = cont + (T->l?T->l->sz:0);
    if(idx<idxt)
        tie(L,T->l) = split(T->l,idx,cont),R = T;
    else  
        tie(T->r,R) = split(T->r,idx,idxt+1),L = T; 
    update(T);
    return {L,R};
}

void insert(Treap *&T,Treap *v,int x, int cnt) {
    lazy(T);
    int idxt = T ? cnt + (T->l ? T->l->sz : 0) : 0;
    if (!T) T = v;
    else if (v->p > T->p)
        tie(v->l, v->r) = split(T, x, cnt), T = v;
    else if (x < idxt) insert(T->l, v, x, cnt);
    else insert(T->r, v, x, idxt + 1);
    update(T);
}

void insert(int e, int i) {
    insert(root, new Treap(e), i-1, 0);
}


Treap *merge(Treap *a,Treap *b){
    lazy(a),lazy(b);
    Treap *T;
    if(!a || !b)T = a?a:b;
    else if(a->p > b->p)
        a->r = merge(a->r,b),T = a;
    else b->l = merge(a,b->l),T = b;
    update(T);
    return T;
}


void erase(Treap *&T,int x ,int cnt = 0){
    if(!T)return;
    lazy(T);
    int left = cnt+(T->l? T->l->sz:0);
    if(left == x)T = merge(T->l,T->r);
    else if(x<left)erase(T->l,x,cnt);
    else erase(T->r,x,left+1);
    update(T);
}

void print(Treap *t) {
    if (!t) return;
    lazy(t);
    print(t->l);
    cerr(to_string(t->val));
    cerr(" ");
    // cout << t->val<<" ";
    print(t->r);
}
void push_back(int e) {
    root = merge(root, new Treap(e));
}


void op(int l,int r, function<void(Treap *T)> f){
    Treap *a,*b,*c;
    tie(a,b) = split(root,l-1);
    tie(b,c) = split(b,r-l);
    f(b);
    root = merge(a, merge(b,c));
}

void reverse(int l,int r){
    op(l,r,[&](Treap *T){applyRev(T);});
}

void rotate(int l,int r,int k){
    op(l,r,[&](Treap *T){
        Treap *l,*r;
        k%=T->sz;
        tie(l,r) = split(T,T->sz-k-1);
        T = merge(r,l);
    });
}

void add(int l,int r,int x){
    op(l,r,[&](Treap *T){
        applySum(T,x);
    });
}

void replace(int l,int r,int x){
    op(l,r,[&](Treap *T){
        applyReplace(T,x);
    });
}

int get_sum(int l,int r){
    int ans;
    op(l,r,[&](Treap *T){
        ans = T->sum;
    });
    return ans;
}

int get_min(int l,int r){
    int mn;
    op(l,r,[&](Treap *T){
        mn = T->mn;
    });
    return mn;
}

int maxn = 150007;
vector<int> st(4*maxn);
vector<int> lazyST(4*maxn);
int n;
void propagate(int v,int l ,int r){
    if(!lazyST[v])return ;
    st[v] += ((r-l)+1)*lazyST[v];
    if(l!= r){
        lazyST[v<<1] += lazyST[v];
        lazyST[v<<1|1]+= lazyST[v];
    }
    lazyST[v] = 0;
}

void update(int l,int r,int val,int v = 1,int sl = 0,int sr = n-1){
    propagate(v,sl,sr);
    if(r<sl || l>sr || sl>sr)return ;
    if(sl>= l && sr<=r){
        lazyST[v] += val;
        propagate(v,sl,sr);
        return;
    }
    int m = (sl+sr)>>1;
    update(l,r,val,v<<1,sl,m);
    update(l,r,val,v<<1|1,m+1,sr);
    st[v] = st[v<<1]+st[v<<1|1];
}

int query(int l,int r,int v = 1,int sl = 0,int sr = n-1){
    propagate(v,sl,sr);
    if(r<sl || l>sr || sl>sr)return 0;
    if(sl>= l && sr<=r)return st[v];
    int m = (sl+sr)>>1;
    return query(l,r,v<<1,sl,m)+query(l,r,v<<1|1,m+1,sr);
}
void printseg(int n){
    for(int i = 0;i<n;i++)
        cout<<query(i,i)<<" ";
    cout<<endl;
}
signed main(){__
    cin>>n;
    vector<int> nums(n);
    for(auto &c:nums)cin>>c;
    map<int,int> b;
    map<int,int> b2;
    map<int,set<int>> pos;
    for(int i = 0;i<n;i++)
        insert(nums[i],i);
    for(int i = n-1;i>=0;i--){
        b[nums[i]]++;
        if(b[nums[i]]>=2)b2[nums[i]] =b[nums[i]]; 
        pos[nums[i]].push_back(i);
    }

    for(auto c:b2){
        cout<<c.first<<" "<<c.second<<endl;
    }
    while(b2.size()){
        int mn = b2.begin()->first;
        cout<<mn<<" "<<b2[mn]<<endl;
        for(auto c:pos[mn])cout<<c<<" ";
        cout<<endl;
        cout<<pos[mn].back()<<endl;
        erase(root,pos[mn].back()+query(pos[mn].back(),pos[mn].back()));
        print(root);
        cout<<endl;
        update(pos[mn].back(),n-1,-1);
        pos[mn].pop_back();
        int ofset = query(pos[mn].back(),pos[mn].back());
        cout<<pos[mn].back()<<" "<<ofset<<endl;
        add(pos[mn].back()+ofset,pos[mn].back()+ofset,mn);
        print(root);
        cout<<endl;
        b[mn*2]++;
        b[mn]-=2;
        pos[mn*2].insert(pos[mn].back())
        pos[mn].pop_back();
        if(b[mn*2]>=2)b2[mn*2] = b[mn*2];
        // b2[mn*2]++;

        b2[mn]-=2;
        if(b2[mn]<=1){
            b2.erase(mn);
        }
        printseg(n);
    }   
    print(root);
    cout<<endl;
    return 0;
}  
