#include <bits/stdc++.h>
using namespace std;
const int maxn = 1007;
vector<int> num(maxn);
vector<int> graph[maxn];

void add_edge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
bool flag = false;
void dfs(int u,int p = -1){
    int mn = 1000000007;
    int mx = -1;
    int gcd = 0;
    for(auto v:graph[u]){
        if(v == p)continue;
        dfs(v,u);
        gcd = __gcd(num[v],gcd);
        mn = min(num[v],mn);
        mx = max(num[v],mx);
    }
    if(mn == mx){
        int mxdiv = 1;
        for(int i = 1;i*i<=gcd;i++){
            if(gcd%i == 0){
                mxdiv = max(i,mxdiv);
                if(i!= 1)
                    mxdiv = max(gcd/i,mxdiv);
            }
        }
        if(mxdiv>=gcd)flag = true;
        num[u]= mxdiv;
    }
    else if(num[u] == -1 && gcd< mn)num[u] = gcd;
    else if(num[u]== -1 && gcd>=mn){flag = true;}
}

int main(){
    // freopen("divisibility-tree.in", "r", stdin);
	// freopen("divisibility-tree.out", "w", stdout);
    int n,x,p;
    cin>>n;
    for(int i = 0;i<n;i++){
        cin>>p>>x;
        num[i] = x;
        if(i)
            add_edge(p-1,i);
    }
    dfs(0);
    for(int i = 0;i<n;i++){
        if(flag)cout<<-1<<" ";
        else
            cout<<num[i]<<" ";
    }
    cout<<endl;
    return 0;
}
// 5
// -1 -1
// 1 2
// 1 -1
// 3 6
// 3 8