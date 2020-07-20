#pragma GCC optimize("unroll-loops")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <bits/stdc++.h>
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
#define endl '\n'
int n;
const int maxn =500007;
#define x first 
#define y second
vector<pair<int,int>>graph[maxn];

void add_edge(int u,int v,int c){
    graph[u].push_back({v,c});
    graph[v].push_back({u,c});
}
int sz[maxn],pa[maxn],head[maxn],stpos[maxn],lvl[maxn],cost[maxn];
vector<int> st;
vector<int> heavy(maxn,-1);

void update(int pos,int val,int v = 1,int sl = 0,int sr = n-1){
    if(sl == sr){
        st[v]= val%2;
        return ;
    }
    int mid = (sl+sr)>>1;
    if(pos<=mid)    
        update(pos,val,v<<1,sl,mid);
    else 
        update(pos,val,v<<1|1,mid+1,sr);
    st[v]= st[v<<1]^st[v<<1|1];
}
int queryst(int l,int r,int v = 1,int sl = 0,int sr = n-1){
    if(l>sr || r<sl || sl>sr)return 0;
    if(sl>=l && sr<=r)return st[v];
    int mid = (sl+sr)>>1;
    return queryst(l,r,v<<1,sl,mid)^queryst(l,r,v<<1|1,mid+1,sr);
}

void dfs(int u,int p = -1,int dep = 0){
    lvl[u]= dep;
    sz[u] =1;
    pa[u] = p;
    int mx = -1;
    for(auto v:graph[u]){
        if(v.x == p)continue;
        cost[v.x] = v.y;
        dfs(v.x,u,dep+1);
        if(sz[v.x]>mx){
            mx = sz[v.x];
            heavy[u]= v.x;
        }
        sz[u]+=sz[v.x];
    }
}

void HLD(){
    for(int i = 0,curr = 0;i<n;i++){
        if(pa[i]== -1 || heavy[pa[i]] != i){
            for(int j = i;j!= -1;j = heavy[j]){
                head[j] = i;
                stpos[j]= curr++;
            }
        }
    }
}   

int query(int u,int v){
    int res = 0;
    while(head[u]!= head[v]){
        if(lvl[u]<lvl[v])
            swap(u,v);
        res ^= queryst(stpos[head[u]],stpos[u]);
        u = pa[head[u]];
    }
    if(lvl[u]> lvl[v])
        swap(u,v);
    if(stpos[u]+1<= stpos[v])
        res^= queryst(stpos[u]+1,stpos[v]);
    return res;
}


int main(){__
    int u,v,c,q,type,idx,l;
    cin>>n;
    st.resize(4*n);
    vector<pair<int,int>> edges;
    for(int i = 0;i<n-1;i++){
        cin>>u>>v>>c;
        u--,v--;
        add_edge(u,v,c);
        edges.push_back({u,v});
    }
    dfs(0);
    HLD();
    for(int i= 1;i<n;i++)
        update(stpos[i],cost[i]);;
    cin>>q;
    for(int i = 0;i<q;i++){
        cin>>type;
        if(type == 1){
            cin>>u>>v;
            u--,v--;
            int x = query(u,v);
            if(!x)cout<<"JAKANDA FOREVER"<<endl;
            else cout<<"WE NEED BLACK PANDA"<<endl;
        }
        else {
            cin>>idx>>l;
            idx--;
            u = edges[idx].x;
            v = edges[idx].y;
            if(pa[v] == u)
                update(stpos[v],l);
            
            else update(stpos[u],l);
        }
    }
    return 0;
}