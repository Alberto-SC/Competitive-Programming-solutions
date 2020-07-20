#include <bits/stdc++.h>
using namespace std;
int gcd(int a,int b,int &x,int &y){
    if(b == 0){x = 1;y = 0;return a;}
    int r = gcd(b,a%b,y,x);
    y-= a/b*x;
    return r;
}
bool find_any_solution(int a,int b,int c,int &x0, int &y0,int &g){
    g = gcd(abs(a),abs(b),x0,y0);
    if(c % g)
        return false;
    x0 *= c / g;
    y0 *= c / g;
    if(a<0)x0 = -x0;
    if(b<0)y0 = -y0;
    return true;
}
int main(){
    int a,b,c;
    cin>>a>>b>>c;
    int x,y,g;
    if(find_any_solution(a,b,c,x,y,g)){
        cout<<x<<" "<<y<<endl;
        if(x>=0 && y>=0)
            cout<<"Yes\n";
        else cout<<"NO\n";
    }
    else cout<<"No\n";
    return 0;
} 