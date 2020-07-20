#include <bits/stdc++.h>
using namespace std;
const int maxn =100007;
vector<int> graph[maxn];
void add_edge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
vector<int> dis(maxn,-1);
vector<int> dis2(maxn,-1);
pair<int,int> BFS(int s,int n,int who){
    queue<int> q;
    q.push(s);
    if(who){
        dis.assign(n,-1);
        dis[s] = 0;
    }
    else {
        dis2.assign(n,-1);
        dis2[s] = 0;
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v:graph[u]){
            if(who){
                if(dis[v]== -1){
                    dis[v] = dis[u]+1;
                    q.push(v);
                }
            }
            else {
                if(dis2[v]== -1){
                    dis2[v] = dis2[u]+1;
                    q.push(v);
                }
            }
        }
    }
    int maxd = 0,idx;
    if(who){

        for(int i = 0;i<n;i++){
            if(dis[i]>maxd){
                maxd = dis[i];
                idx = i;
            }
        }
    }
    else {
        for(int i = 0;i<n;i++){
            if(dis2[i]>maxd){
                maxd = dis2[i];
                idx = i;
            }
        }
    }
    return {idx,maxd};
}

int n,k,u,v;
bool dfs(int u,int p = -1,int lvl = 0){
    int cont = 0;
    for(auto v:graph[u]){
        if(v == p)continue;
        cont++;
        if(!dfs(v,u,lvl+1))return false;
    }
    // cout<<u<<" "<<cont<<endl;
    if(cont == 1 ||cont == 2)return false;
    if(cont == 0 && lvl != k)return false;
    return true;
}

int main(){
    cin>>n>>k;
    for(int i = 0;i<n-1;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v);
    }
    // auto c = BFS(0,n,);
    // cout<<c.first<<" "<<c.second;
    auto c = BFS(BFS(0,n,0).first,n,1);
    int x = c.second;
    BFS(c.first,n,0);
    // cout<<x<<endl;
    int root = -1;
    for(int i = 0;i<n;i++){
        // cout<<dis[i]<<" "<<dis2[i]<<endl;;
        if(dis[i]== dis2[i] && dis[i] == x/2 && root != -1)return cout<<"No"<<endl,0;
        if(dis[i]== dis2[i] && dis[i] == x/2)root = i;
    }
    // cout<<root<<endl;
    if(dfs(root))cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    cout<<endl;

    return 0;
}