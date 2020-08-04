// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli rand(lli a, lli b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1])); 
    lli t,n;
    t = rand(1, 10);
    cout<<t<<endl;
    while(t--){
        n = rand(0,1000000000000000000);
        cout<<n<<endl;
    }
}
    
