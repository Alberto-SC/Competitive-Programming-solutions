#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    long double cost,l,h,ans = 0;
    cin>>cost>>n;
    for(int i = 0;i<n;i++){
        cin>>l>>h;
        ans += l*h*cost;
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(7);
    cout<<ans;

    return 0;
}