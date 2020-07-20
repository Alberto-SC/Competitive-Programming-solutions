#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
const lli m = 188888867;
const int maxn = 100007;

lli mod_pow(lli a,lli b){
    lli x = 1;
    while(b){
        if(b&1)x = (x*a)%m;
        a = (a*a)%m;
        b>>=1;
    }
    return x;
}
vector<int> graph[maxn];
vector<int> dist(maxn);
vector<int> digits(maxn);
vector<int> c(maxn);
vector<string> str(maxn);
lli pa[25][maxn];
lli codetoR[maxn];
lli codetov[maxn];
vector<int> padre(maxn,0);
void add_edge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void dfs2(int s){
    int p = 0;
    vector<bool> visited(maxn, false);
    stack<int> st;
    st.push(s); 
    dist[0] = 0;
    digits[0] = ceil(log10((c[0]+1)*1.0));
    // str[0] = "$"+c[0];
    codetov[0] = c[0];
    codetoR[0] = c[0];
    while(!st.empty()){
        int u = st.top();
        st.pop();
        if(!visited[u]){
            if(u!= 0){
                dist[u] = dist[pa[0][u]]+1;
                digits[u]= digits[pa[0][u]]+ceil(log10((c[u]+1)*1.0));
                // str[u] = str[pa[0][u]]+"$"+c[u];
                lli x = codetov[pa[0][u]];
                lli y = mod_pow(10,ceil(log10((c[u]+1)*1.0)));
                lli z = x*y;
                z+=c[u];
                z%=m;
                codetov[u] = z;
                x = c[u];
                y = mod_pow(10,digits[pa[0][u]]);
                x*=y;
                x+=codetoR[pa[0][u]];
                x%=m;
                codetoR[u] = x;
            }
            // mod(u,str[u]);
            visited[u]= true;
        }
        for(auto v:graph[u]){
            if(!visited[v]){
                pa[0][v] = u;
                st.push(v);
            }
        }
    }
}

void precalc(int n){
    memset(pa,-1,sizeof(pa));
    dfs2(0);
    for(int i = 1;i<25;i++){
        for(int j = 0;j<n;j++){
            if(pa[i-1][j]== -1)continue;
            pa[i][j] = pa[i-1][pa[i-1][j]];
        }
    }
}

int lca(int u,int v){
    if(dist[u]>dist[v])swap(u,v);
    int diff = dist[v]-dist[u];
    for(int i = 24;i>=0;i--){
        if(pa[i][v]==-1)continue;
        if((diff>>i) & 1) v = pa[i][v];
    }
    if(u == v)return u;

    for(int i  = 24;i>= 0;i--){
        if(pa[i][u]!= pa[i][v]){
            u = pa[i][u];
            v = pa[i][v];
        }
    }
    return pa[0][u];
}

int main(){
    int n,k,u,v;
    cin>>n>>k;
    for(int i = 0;i<n;i++){
        cin>>c[i];
    }
    for(int i = 0;i<n-1;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v);
    }
    precalc(n);
    for(int i = 0;i<k;i++){
        cin>>u>>v;
        u--,v--;
        if(u == 0){cout<<codetov[v]<<endl;continue;}
        if(v == 0){cout<<codetoR[u]<<endl;continue;}
        int _lca = lca(u,v);
        lli x = 0,y ,z,a,b;
        if(u != _lca){
            x = codetoR[u]-codetoR[_lca];
            if(x<0)x+=m;
            y = mod_pow(10,digits[_lca]);
            y = mod_pow(y,m-2);
            x*=y;
            x%=m;
            x*=mod_pow(10,digits[v]-digits[pa[0][_lca]]);
            x%=m;
        }
        a = codetov[v];
        b = codetov[pa[0][_lca]];
        if(lca== 0)
            b*=mod_pow(10,digits[v]);
        else
            b*=mod_pow(10,digits[v]-digits[pa[0][_lca]]);
        b%=m;
        a-=b;
        if(a<0)a+=m;
        z = x+a;
        z%=m;
        cout<<z<<endl;
    }
    return 0;
}