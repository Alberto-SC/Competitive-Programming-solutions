// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;
int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {

    srand(atoi(argv[1])); 
    int t,n;
    n = rand(1, 30);
    cout<<n<<endl;    
    for(int i = 0;i<n-1;i++){
        int u = rand(1,100);
        cout<<u<<" ";
    }
    cout<<endl;
}
    
