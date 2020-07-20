#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
#define x first 
#define y second
typedef long long int lli;
const lli maxn = 500007;
vector<pair<lli,lli>> graph[maxn];
vector<lli> dist(maxn);
vector<lli> st;
vector<lli> lazy;
const lli inf  = 1e15+7;
void add_edge(lli u,lli v,lli c){
    graph[v].push_back({u,c});
    graph[u].push_back({v,c});
}   
struct Query{
    lli v,l,r,idx;
    bool operator <(const Query A)const{
        return v<A.v;
    }
};


vector<lli>ans;

void propagate(lli v,lli l,lli r){
    if(lazy[v] == 0)return ;
    st[v] += lazy[v];
    if(l != r){
        lazy[v<<1]+= lazy[v];
        lazy[v<<1|1] += lazy[v];
    }
    lazy[v] = 0;
}

lli n,m,u,v,c,l,r;

void update(lli l,lli r ,lli val,lli v = 1,lli sl = 0,lli sr = n-1){
    propagate(v,sl,sr);
    if(r<sl || l>sr || sl>sr)return;
    if(sl>=l &&sr <=r){
        lazy[v] +=val;
        propagate(v,sl,sr);
        return;
    }
    lli mid = (sl+sr)>>1;
    update(l,r,val,v<<1,sl,mid);
    update(l,r,val,v<<1|1,mid+1,sr);
    st[v] = min(st[v<<1],st[v<<1|1]);
}

lli query(lli l,lli r,lli v = 1,lli sl = 0,lli sr = n-1){
    propagate(v,sl,sr);
    if(r<sl || l>sr || sl>sr)return inf;
    if(sl>=l && sr<=r)return st[v];
    lli mid = (sl+sr)>>1;
    return min(query(l,r,v<<1,sl,mid), query(l,r,v<<1|1, mid+1,sr));
}
vector<pair<lli,lli>> pos(maxn); 
lli idx = 0;
vector<bool> leaf(maxn,false);
void dfs(lli u,lli p = -1,lli d = 0){
    dist[u]= d;
    pos[u].x  =idx;
    lli cont = 0;
    for(auto v:graph[u]){
        if(v.x == p)continue;
        idx++;
        dfs(v.x,u,d+v.y);
        cont++;
    }
    if(!cont)leaf[u] = true;
    pos[u].y = idx;
}
vector<Query> q;
void dfs2(lli u ,lli w,lli p = -1){
    if(pos[u].x-1>=0)
        update(0,pos[u].x-1,w);
    if(pos[u].y+1<n) 
        update(pos[u].y+1,n-1,w); 
    update(pos[u].x,pos[u].y,-w);
    while(idx<q.size() && q[idx].v== u){
        ans[q[idx].idx] = query(q[idx].l,q[idx].r);
        idx++;
    }
    for(auto v:graph[u]){
        if(v.x== p)continue;
        dfs2(v.x,v.y,u);
    }
    update(pos[u].x,pos[u].y,w);
    if(pos[u].x-1>=0)
        update(0,pos[u].x-1,-w);
    if(pos[u].y+1<n) 
        update(pos[u].y+1,n-1,-w); 

}

int main(){__
    cin>>n>>m;
    st.resize(4*n);
    lazy.resize(4*n);
    for(lli i = 0;i<n-1;i++){
        cin>>v>>c;
        u--,v--;
        add_edge(i+1,v,c);
    }
    for(lli i = 0;i<m;i++){
        cin>>v>>l>>r;
        v--,l--,r--;
        q.push_back({v,l,r,i});
    }
    ans.resize(m);
    sort(q.begin(),q.end());
    dfs(0);
    for(lli i = 0;i<n;i++){
        if(leaf[i])
            update(pos[i].x,pos[i].x,dist[i]);
        else update(pos[i].x,pos[i].x,inf);
    }
    idx = 0;
    dfs2(0,0);
    for(auto c:ans)cout<<c<<endl;
    return 0;
}

