#include <bits/stdc++.h>
using namespace std;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
vector<pair<int,int>> points;
vector<int> ans;
int x,y,n,a,b;

int dist(int ini,int fin){
	int distx = (points[ini].first-points[fin].first);
	int disty = (points[ini].second-points[fin].second);
	return (distx*distx)+(disty*disty);
}

int main(){__
    cin>>x>>y;
    cin>>n;
    points.push_back({x,y});
    for(int i = 0;i<n;i++){
        cin>>a>>b;
        points.push_back({a,b});
    }
    vector<int> print((1<<n)+7,0);
    vector<int> dp((1<<n)+7,0);
    for(int m = 1;m<(1<<n);m++){
        int i;
        for(int j = 0;j<n;j++)
            if((m>>j)&1){i = j;break;}
        print[m] = i+1;
        dp[m] = dp[m^(1<<i)]+(2*dist(0,i+1));
        for(int j = i+1;j<n;j++){
            if((m>>j)&1){
                int x = dist(0,i+1)+dist(i+1,j+1)+dist(j+1,0);
                x+=dp[m^(1<<i)^(1<<j)];
                if(x<dp[m]){
                    dp[m] = x;
                    print[m] = (i+1)*100+(j+1);
                }
            }
        }
    }
    cout<<endl;
    int mask = (1<<n)-1;
    cout<<dp[mask]<<endl;
    cout<<0<<" ";
    while(mask){
        int a,b;
        a = print[mask]%100;
        b = print[mask]/100;
        if(a)cout<<a<<" ",mask^=(1<<(a-1));
        if(b)cout<<b<<" ",mask^=(1<<(b-1));
        cout<<0<<" ";
    }
    cout<<endl;
    return 0;
}