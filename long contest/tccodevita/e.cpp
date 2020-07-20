#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
vector<int> h;
vector<int> padre;
lli lcm(lli a,lli b){
    return b*(a/__gcd(a,b));
}
lli lcm(vector<lli> & nums){
    lli ans = 1; 
    for(lli & num : nums) ans = lcm(ans, num);
    return ans;
}
struct disjointSet{
	int N;
	vector<short int> rank;
	vector<int> parent, count;
	disjointSet(int N): N(N), parent(N), count(N), rank(N){}
	void makeSet(int v){
		count[v] = 1;
		parent[v] = v;
	}
	int findSet(int v){
		if(v == parent[v]) return v;
		return parent[v] = findSet(parent[v]);
	}
	void unionSet(int a, int b){
		a = findSet(a), b = findSet(b);
		if(a == b) return;
		if(rank[a] < rank[b]){
			parent[a] = b;
			count[b] += count[a];
		}else{
			parent[b] = a;
			count[a] += count[b];
			if(rank[a] == rank[b]) ++rank[a];
		}
	}
};
int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    lli t,n;
    cin>>t;
    while(t--){
        cin>>n;
        disjointSet DSU(n);
        vector<lli> monkey(n);
        for(auto &x:monkey){cin>>x;x--;}
        vector<lli> iter(n,0);  
        for(auto c:DSU.parent)cout<<" ";
        cout<<endl;
        for(int i = 0;i<n;i++)
            DSU.unionSet(i,monkey[i]);
        // map<int,int> mapa;
        // for(auto c:padre)mapa[c]++;
        // for(int i =0;i<n;i++)
        //     iter[i] = mapa[padre[i]];
        cout<<lcm(iter)<<"\n";
    }
    return 0;
}