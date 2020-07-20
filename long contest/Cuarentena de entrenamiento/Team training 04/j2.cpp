#include <bits/stdc++.h>
using namespace std;
const int maxn = 500007;
#define x first 
#define y second
#define endl '\n'
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
map<int,int> mp;
vector<pair<int,int>> graph[maxn];
vector<int> st;
vector<int> lazy;
vector<int> depth(maxn);
vector<pair<int,int>> ranges(maxn);
int parent[25][maxn];
void add_edge(int u,int v,int c){
    graph[u].push_back({v,c});
    graph[v].push_back({u,c});
}
vector<int> dist(maxn);
void dfs(int u,int &idx,int p = -1,int d = 0,int dp =0){ 
    ranges[u].x = idx;
    dist[u]  = d%2;
    depth[u] = dp;
    for(auto v:graph[u]){
        if(v.x == p)continue;
        dfs(v.x,++idx,u,(d+v.y)%2,dp+1);
    }
    ranges[u].y = idx;
}

void build(int v,vector<int> &A,int l,int r){
    if(l == r)st[v] = A[l];
    else{
        int m = (l+r)>>1;
        build(v*2,A,l,m);
        build(v*2+1,A,m+1,r);
        st[v] = st[v*2] +st[v*2+1];
    }
}

void propagate(int v,int l ,int r){
    if(lazy[v] == 0)return;
    st[v] = (st[v]+=lazy[v])%2;
    if(l != r){
        lazy[v<<1]  = (lazy[v<<1] + lazy[v])%2;
        lazy[v<<1|1]= (lazy[v<<1|1] + lazy[v])%2;
    }
    lazy[v]=0;
}
void update(int v,int sl,int sr,int l,int r,int val){
    propagate(v,sl,sr);
    if(l>sr || r <sl)return;
    if(sl>= l && sr<= r){
        lazy[v]+=val%2;
        propagate(v,sl,sr);
        return;
    }
    int m = (sl+sr)>>1;
    update(v*2,sl,m,l,r,val);
    update(v*2+1,m+1,sr,l,r,val);
    st[v] = (st[v*2]+st[v*2+1])%2;
}


int query(int v ,int sl ,int sr,int l,int r){
    propagate(v,sl,sr);
    if(l>sr || r <sl || sl>sr)return 0;
    if(sl>=l && sr<=r)return st[v];
    int m = (sl+sr)>>1;
    return query(v*2,sl,m,l,r)+query(v*2+1,m+1,sr,l,r);
}

int main(){__
    int n,u,v,q,tp,z,c,val,idx = 0; 
    cin>>n;
    vector<pair<int,int>> edges(n-1);
    vector<int> cost(n-1);
    for(int i = 0;i<n-1;i++){
        cin>>u>>v>>c;
        u--,v--;
        cost[i] = c;
        edges[i] = {u,v};
        add_edge(u,v,c);
    }
    st.resize(4*n);
    lazy.resize(4*n);
    dfs(0,idx);
    vector<int> t(n);
    for(int i = 0;i<n;i++)
        t[ranges[i].x] = dist[i];
    build(1,t,0,n-1);
    cin>>q;
    for(int i= 0;i<q;i++){
        cin>>tp;
        if(tp == 1){ 
            cin>>u>>v;
            u--,v--;
            int x =query(1,0,n-1,ranges[u].x,ranges[u].x);
            x^=query(1,0,n-1,ranges[v].x,ranges[v].x);
            if(x%2)cout<<"WE NEED BLACK PANDA"<<endl;
            else cout<<"JAKANDA FOREVER"<<endl;
        }
        else{
            cin>>idx>>val;
            idx--;
            u = edges[idx].x;
            v = edges[idx].y;
            if(depth[u]<depth[v])swap(u,v);
            int dif = val-cost[idx];
            update(1,0,n-1,ranges[u].x,ranges[u].y,dif);
            cost[idx] = val;
        }
    }
    return 0;
}