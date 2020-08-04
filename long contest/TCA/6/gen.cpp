// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {

    srand(atoi(argv[1])); 
    int n,m;
    n = 1000000;
    m = rand(100000,n);
    cout<<n<<" "<<m<<endl;
    for(int i = 0;i<n;i++)
        cout<<char(rand(0,1)+'a');
    
    cout<<endl;
    for(int i= 0;i<m;i++)
        cout<<char(rand(0,1)+'a');
    
}
    
