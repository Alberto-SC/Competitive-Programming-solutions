#include <bits/stdc++.h>
using namespace std;
vector<int> st;
const int maxn = 300007;
vector<int> a;
vector<int> graph[maxn];
vector<int> lazy;
int pa[maxn][26];
int depth[maxn];



void add_edge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
int p = 0;
int q[maxn];
int topq = 0;

void dfs(int u,int p = -1,int d = 0){
    depth[u] = d;
    pa[u][0] = p;
    for(auto v:graph[u]){
        if(v== p)continue;
        dfs(v,u,d+1);
    }
} 


void build(){
    dfs(0);
    for(int i = 1;i<mxlog;i++){
        for(int u = 0;u<N;u++){
            if(pa[i-1   ][u]!= -1)
            pa[i][u] = pa[i-1][pa[i-1][u]];
        }
    }
}

int lca(int u,int v){
    if(depth[u]> depth[v])swap(u,v);
    int diff = depth[v]-depth[u];
    for(int i = 25;i>=0;i--){
        if((diff>>i) &1){
            v = pa[v][i];
        }
    }

    if(v == u)return u;
    for(int i = 25;i>=0;i--){
        if(pa[v][i]!= pa[u][i]){
            v = pa[v][i];
            u = pa[u][i]; 
    if(lazy[v] == 0 )return ;
    st[v] +=lazy[v];
    if(l != r){
        lazy[v<<1] +=lazy[v];
        lazy[v<<1|1]+=lazy[v];
    }
    lazy[v] =0;
}
void update(int pos ,int val ,int v = 1,int sl = 0,int sr = n-1){
    propagate(v,sl,sr);
    if(sl>=l && sr<=r){
        lazy[v] += val;
        propagate(v,sl,sr);
        return;
    }
    int mid = (sl+sr)>>1;
    update(pos,val,v<<1,sl,mid);
    update(pos,val,v<<1|1,mid+1,sr);
    st[v] = st[v<<1]+st[v<<1|1];
} 

int query(int l,int r,int v= 1,int sl = 0,int sr = n-1){
    propagate(v,sl,sr);
    if(l>sr || r<sl || sl>sr)return 0;   
    if(sl>=l && sr<=r)return st[v];
    int mid = (sl+sr)>>1;
    return query(l,r,v<<1,sl,mid)+query(l,r,v<<1|1,mid+1,sr);
}

vector<int> ans(maxn);
void dfs2(int u,int p = -1,int ac){
    ans[u] =ac;
    for(auto v: graph[u]){
        dfs2(v,u,ac+query(u,u));
    }
}


vector<int> range_level;
void bfs(int s){
    q[topq++] = s;
    for(int i = 0;i<topq;i++){
        int u = q[i];
        for(int v:graph[u]){
            q[topq++]= v;
            a.push_back(v);
        }
    }
}

int main(){
    int n,v,u,k,x,q;
    cin>>n;
    st.resize(4*n);
    for(int i = 0;i<n;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v);
    }
    cin>>q;
    bfs(0);
    for(auto c:a)cout<<c<<" ";
    cout<<endl;
    for(int i = 0;i<n;i++){
        cin>>v>>k>>x;
        

    }
    return 0;
}