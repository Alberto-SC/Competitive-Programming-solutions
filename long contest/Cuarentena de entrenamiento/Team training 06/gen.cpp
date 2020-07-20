#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long int lli;

lli rand(lli a, lli b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1])); 
    int n = rand(1,10);
    cout<<n<<endl;
    for(int i = 0;i<n;i++){
        lli x = rand(1,10000);
        cout<<x<<" "<<rand(1,x-1)<<" "<<rand(1,10000)<<endl;
    } 
    return 0;
}