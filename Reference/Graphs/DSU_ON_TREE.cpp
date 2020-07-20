#include <bits/stdc++.h>
using namespace std;
void dfs_size(int v ,int p){
    sz[v] = 1;
    for(auto u:graph[v]){
        if(u != p){
            dfs_size(u,v)
            sz[v] +=sz[u];
        }
    }
}
vector<int> *vec[maxn];
int cnt[maxn];
void dfs(int v, int p, bool keep) {
	int Max = -1, bigchild = -1;
	for (auto u : adj[v]) {
		if (u != p && Max < sz[u]) {
			Max = sz[u];
			bigchild = u;
		}
	}
	for (auto u : adj[v]) {
		if (u != p && u != bigchild) {
			dfs(u, v, 0);
		}
	}
	if (bigchild != -1) {
		dfs(bigchild, v, 1);
		swap(vec[v], vec[bigchild]);
	}
	vec[v].push_back(v);
	cnt[color[v]]++;
	for (auto u : adj[v]) {
		if (u != p && u != bigchild) {
			for (auto x : vec[u]) {
				cnt[color[x]]++;
				vec[v].push_back(x);
			}
		}
	}
	if (keep == 0) {
		for (auto u : vec[v]) {
			cnt[color[u]]--;
		}
	}
}
void dfs3(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs3(u, v, 0);  // run a dfs3 on small childs and clear them from cnt
    if(bigChild != -1)
        dfs3(bigChild, v, 1);  // bigChild marked as big and not cleared from cnt
    for(auto u : g[v])
	if(u != p && u != bigChild)
	    for(int p = st[u]; p < ft[u]; p++)
		cnt[ col[ ver[p] ] ]++;
    cnt[ col[v] ]++;
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(keep == 0)
        for(int p = st[v]; p < ft[v]; p++)
	    cnt[ col[ ver[p] ] ]--;
}
typedef vector<int> vi;
vi *V[MAXN];
void dfs2(int v, int par = -1){
	int mx = 0, chl = -1;
	for(auto u : adj[v])if(par - u){
		dfs2(u,v);
		if(mx < V[u]->size()){
			mx = V[u]->size();
			chl = u;
		}
	}
	for(auto u : adj[v])if(par - u and chl - u){
		for(auto a : *V[u])
			V[chl]->push_back(a);
		delete V[u];
	}
	if(chl + 1)
		V[v] = V[chl];
	else{
		V[v] = new vi;
		V[v]->push_back(v);
	}
}
int main(){
    return 0;
}