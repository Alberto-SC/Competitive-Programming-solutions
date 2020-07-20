#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

int main(){__
	int t,h,w;
	cin>>t;
    while(t--){
        cin>>h>>w;
        if(h == w)cout<<"Square"<<endl;
        else cout<<"Rectangle"<<endl;
    }
    return 0;
}  