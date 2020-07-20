#include <bits/stdc++.h>
using namespace std;
const int maxn = 200007;
vector<int> graph[maxn];
vector<int> graph2[maxn];
int N;
void add_edge(int u,int v,bool who){
    if(who){
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    else {
        graph2[u].push_back(v);
        graph2[v].push_back(u);
    }
}


pair<int,int> BFS(int s,bool who){
	queue<int> q;
	vector<int> dis(N,-1);
	q.push(s); 
	dis[s] = 0;
	while( !q.empty() ){
		int u = q.front();
		q.pop();
		for(int v : who?graph[u]:graph2[u]){
			if(dis[v] == -1) {
				dis[v] = dis[u]+1;
				 q.push(v);
			}
		}		
	}

	int maxd= 0,in;
    for(int i = 0;i<N;i++){
        if(dis[i]>maxd){
            maxd = dis[i];
            in = i;
        }

    }
	return make_pair(in,maxd);
}

int main(){
    int n,u,v,m;
    cin>>n;
    for(int i = 0;i<n-1;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v,0);
    }
    N = n;
    int first = BFS(BFS(0,0).first,0).second;
    cin>>m;
    for(int i = 0;i<m-1;i++){
        cin>>u>>v;
        u--,v--;
        add_edge(u,v,1);
    }
    N = m;
    int second = BFS(BFS(0,1).first,1).second;
    // cout<<first<<" "<<second<<endl;
    first++,second++;
    second = (second/2)+1;
    if(first>second)cout<<"GGEZ"<<endl;
    else cout<<"FF"<<endl;
    return 0;
}