#include <bits/stdc++.h>

using namespace std;

#define enld "\n"
typedef long long int lli;

int main(){
	int n,q; cin >> n >> q;

	vector<int> t(n+1,0), qr(n+1,0), sz(n+1,0), c(n+1,0);
	int op,x,sol=0,l=1,r=1;

	for(int i=1; i<=q; i++){
		cin >> op >> x;

		switch(op){
			case 1:
			cout << "case1" << endl;
				qr[++r] = x;
			cout << "p1" << endl;
				t[r]=i;
				cout << "p2" << endl;
				sz[x]++;
				cout << "p3" << endl;
				sol++;
				cout << sol << endl;
			break;

			case 2:
			cout << "case2" << endl;
				c[x]=i;
				sol -= sz[x];
				sz[x] = 0;
				cout << sol << endl;
			break;

			default:
			cout << "case3" << endl;
				while(l <= x){
					if(c[qr[l]] < t[l]){
						sz[qr[l]]--;
						sol--;
					}
					l++;
				}
				cout << sol << endl;
			break;
		}
	}

	return 0;
}