#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);
int main(){
    long double L,R,P;
    cin>>L>>R>>P;
    if(L<R){
        if(isgreaterequal(L,R*(P/100.0)))cout<<"Ambidextrous"<<endl;
        else cout<<"Right-handed"<<endl;
    }
    else{
        if(isgreaterequal(R,L*(P/100.0)))cout<<"Ambidextrous"<<endl;
        else cout<<"Left-handed"<<endl;
    } 
    return 0;
}