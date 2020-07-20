#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
const lli INF = 1000000000000000;
const int maxn = 200007;
#define x first
#define y second
#define endl '\n'
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
vector<pair<lli,lli>> graph[maxn];
vector<lli> D(maxn);
void add_edge(lli u,lli v,lli cost){
    graph[u].push_back({v,cost});
}
void dijkstra(lli s){
  	priority_queue<pair<lli,lli>,vector<pair<lli,lli>>,greater<pair<lli,lli>>> pq;
	pq.push({0,s});
	D[s] = 0;
	while(pq.size()){
		auto act = pq.top(); pq.pop();
		int u = act.y;
		lli d = act.x;
		if(d > D[u])continue;
		for(auto &v : graph[u]){
			if(D[u]+v.y < D[v.x]){
				D[v.x] = D[u]+v.y;
				pq.push({D[v.x],v.x});
			}
		}
	}
}
int main(){__
    lli n,l,r,c;
    cin>>n>>l>>r>>c;
    vector<int> nums(n);
    lli u,v;
    cin>>u>>v;
    u--,v--;
    for(auto &c:nums)cin>>c;
    map<int,int>mp;
    int key= 0;
    for(int i = 0;i<n;i++){
        if(mp.count(nums[i]))continue;
        mp[nums[i]]= key++;
    }
    for(int i=0;i<n+key+1;i++)D[i] = INF;

    for(int i = 0;i<n;i++){
        add_edge(i,mp[nums[i]]+n,c);
        add_edge(mp[nums[i]]+n,i,0);
    }
    for(int i= 0;i<n-1;i++){
        if(i-1 >= 0)
			add_edge(i,i-1,l);
		if(i+1 < n)
            add_edge(i,i+1,r);
        
    } 
    dijkstra(u);
    cout<<D[v]<<endl;
    return 0;
}