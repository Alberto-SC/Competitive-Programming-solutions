#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define mod 51123987

int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<vector<int>> p(2,vector<int>(n,0));
    for(int z = 0,l = 0,r = 0;z<2;z++,l = 0,r = 0){
        for(int i = 0;i<n;i++){
            if(i<r)p[z][i] = min(r-i+!z,p[z][l+r-i+!z]);
            int L = i-p[z][i], R = i+p[z][i] -!z;
            while(L-1>=0 && R+1<n && s[L-1] == s[R+1])p[z][i]++,L--,R++;
            if(R>r) l = L,r = R;
        }
    }
	vector<pair<int,bool>> arrange;
    for(int z = 0;z<2;z++){
        for(int i = 0;i<n;i++){
            for(int j = 0;j<=p[z][i];j++){
                if(z){
                    arrange.emplace_back({(i-j)-1,true});
                    arrange.emplace_back({i+j,false});
                }
                else {
                    if(j!= 0){
                        arrange.emplace_back({(i-j)-1,true});
                        arrange.emplace_back({i+(j-1),false});
                    }
                }
            }
        }
    }
    // for(auto &c:ranges)c.first++,c.second++;
    // for(auto c:ranges)cout<<c.first<<" "<<c.second<<endl;
    // cout<<c.first<<" "<<c.second<<endl;
    //for(int i = 0;i<n;i++)cout<<p[0][i]<<" "<<p[1][i]<<endl;
	

	sort(arrange.begin(), arrange.end());
	lli sum = 0, act = 0;
	for(auto p:arrange){
		if(p.second){
			sum = (sum+act)%mod;
			act++;
		}
		else{
			act--;
		}
	}

	cout << sum << endl;


    return 0;
}