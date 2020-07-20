#include <bits/stdc++.h>
 
#define endl "\n"
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);
 
using namespace std;
 
typedef long long int lli;
vector<pair<int,int>> v;
int lim,n;
bool check(unsigned int *a){
	for(int i=0; i<lim; i++){
		vector<pair<int,char>> ans;
		for(int j=0; j<n; j++){
			if(i&(1<<j)){
				ans.push_back(make_pair(j,'a'));
			}else{
				ans.push_back(make_pair(j,'b'));
			}
		}

		int back,front;
		bool isAns = true;
		for(int i=1; i<ans.size(); i++){
			back = (ans[i-1].second=='a')?v[a[ans[i-1].first]].second:v[a[ans[i-1].first]].first;
			front = (ans[i].second=='a')?v[a[ans[i].first]].first:v[a[ans[i].first]].second;

			if(front != back)
				isAns = false;
		}

		if(isAns){
			for(auto p:ans)
				cout << a[p.first]+1 << " " << p.second << endl;
			return true;
		}
	}
	return false;
} 

void fast_permutation(void){
    unsigned int a[n], p[n+1];
    register unsigned int i, j, tmp;
    for(i = 0; i < n; i++){
        a[i] = i;   
        p[i] = i;
    }
    p[n] = n;
    if(check(a))return;  
    i = 1;   
    while(i < n){
        p[i]--;          
        j = i % 2 * p[i];  
        tmp = a[j];         
        a[j] = a[i];
        a[i] = tmp;
		if(i+1<n && v[a[i]].first != v[a[i+1]].first && v[a[i]].first != v[a[i+1]].second && v[a[i]].second != v[a[i+1]].first && v[a[i]].second != v[a[i+1]].second);
		else if(i-1>=0 && v[a[i]].first != v[a[i-1]].first && v[a[i]].first != v[a[i-1]].second && v[a[i]].second != v[a[i-1]].first && v[a[i]].second != v[a[i-1]].second); 
		else if(check(a))return;
        i = 1;              
        while (!p[i]){
            p[i] = i;       
            i++;     
        }
    } 
} 
 
int main(){
	fast_io
	cin >> n;
	int a,b;
	for(int i=0; i<n; i++){
		cin >> a >> b;
		v.push_back(make_pair(a,b));
	}
	lim = (1<<n)+1;
	fast_permutation(); 
	return 0;
}