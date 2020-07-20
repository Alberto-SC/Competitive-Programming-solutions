// generating a random sequence of distinct elements
#include <bits/stdc++.h>
using namespace std;
int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {

    srand(atoi(argv[1])); 
    int t,n;
    t = rand(1, 100);
    cout<<t<<endl;
    while(t--){
        n = rand(1,40);
    
        for(int i = 0;i<n;i++){
            int u = rand(0,26);
            u+='a';
            cout<<char(u);
        }
        cout<<endl;
    }
}
    
