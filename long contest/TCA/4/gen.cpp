// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1])); 
    int t,n;
    n = rand(1, 1000);
    cout<<n<<endl;
    for(int i = 0;i<n;i++){
        int u = rand(1000000000,1000000000);
        cout<<u<<" ";
    }
    cout<<endl;
    int q = rand(1,100);
    cout<<q<<endl;
    for(int i = 0;i<q;i++){
        int l,r;
        l = rand(1,n);
        r = rand(l,n);
        cout<<l<<" "<<r<<endl;
    }
    
}
    
