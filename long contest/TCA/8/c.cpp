#include <bits/stdc++.h>
using namespace std;
const int maxn = 100007;
vector<int> graph[maxn];

int q[maxn];
int n;
int dis[2][maxn];
int sz[maxn];
void add_edge(int u,int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}
pair<int,int> BFS(int s,int who){
	queue<int> q;
    for(int i = 0;i<n;i++)dis[who][i] = -1;
	q.push(s); 
	dis[who][s] = 0;
	while( !q.empty() ){
		int u = q.front();
		q.pop();
		for(int v : graph[u]){  
			if(dis[who][v] == -1) {
				dis[who][v] = dis[who][u]+1;
				 q.push(v);
			}
		}		
	}

	int maxd= 0,in;
		for(int i = 0;i<n;i++){
			if(dis[who][i]>maxd){
				maxd = dis[who][i];
				in = i;
			}

		}
	return make_pair(in,maxd);
}

int parent[maxn];  
    sz[u] = 1;
    for(auto v:graph[u]){
        if(v == p)continue;
        dfs(v,u);
        sz[u]+= sz[v];
    }
}

int main(){
    int u,v;
    cin>>n;
    for(int i = 0;i<n-1;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v);
    }
    u = BFS(0,0).first;
    v = BFS(u,1).first;
    cout<<u<<" "<<v<<endl;
    cout<<BFS(u,1).second<<endl;    
    dfs(u);
    vector<int> path;
    for(int i = 0;i<n;i++)  
        cout<<dis[0][i]<<" ";
    cout<<endl;
    for(int i = 0;i<n;i++)
        cout<<dis[1][i]<<" ";
    cout<<endl;
    while(parent[v] != -1){
        v = parent[v];
        path.push_back(v);
    }   
    path.pop_back();
    for(auto c:path)cout<<c<<" ";
    for(int i = 0;i<n;i++){

    }
    cout<<endl;
    return 0;
}