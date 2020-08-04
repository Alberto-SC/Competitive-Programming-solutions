#include <bits/stdc++.h>
using namespace std;
const int maxn = 1007;
vector<int> num(maxn);
vector<int> graph[maxn];
#define endl '\n'
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
void add_edge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
bool flag = false;
void dfs(int u,int p = -1){
    int mx = -1;
    int gcd = 0;
    for(auto v:graph[u]){
        if(v == p)continue;
        dfs(v,u);
        gcd = __gcd(num[v],gcd);
    }
    if(num[u] == -1)num[u] = gcd;
}
int getMin(int u,int p){
    int mn = 1000000007;
    for(int i = 1;i*i<=p;i++){
        if(p%i == 0){
            if(i>u && i%u==0)mn = min(mn,i);
            if((p/i)>u && (p/i) %u == 0)mn = min(mn,p/i);
        }
    }
    if(mn != 1000000007)return mn;
    return u;
}

vector<bool> leafs(maxn);
void dfs2(int u,int p = -1){
    if(u != 0){
        int x = getMin(num[p],num[u]);
        if(x <= num[p])flag = true;
        else if(!leafs[u])num[u] = x;
    }
    else num[u] = 1;
    for(auto v:graph[u]){
        if(v == p)continue;
        dfs2(v,u);
    }
}

int main(){__
    // freopen("divisibility-tree.in", "r", stdin);
	// freopen("divisibility-tree.out", "w", stdout);
    int n,x,p;
    cin>>n;
    for(int i = 0;i<n;i++){
        cin>>p>>x;
        num[i] = x;
        if(x!= -1)leafs[i] = true;
        if(i)
            add_edge(p-1,i);
    }
    if(n ==1)return cout<<num[0]<<endl,0;
    dfs(0);
    dfs2(0);
    for(int i = 0;i<n;i++){
        if(flag)cout<<-1<<" ";
        else
            cout<<num[i]<<" ";
    }
    cout<<endl;
    return 0;
}