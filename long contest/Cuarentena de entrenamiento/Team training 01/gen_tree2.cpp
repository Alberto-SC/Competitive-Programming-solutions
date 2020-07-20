// generating a tree in a not-so-stupid way
#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));
    int t = rand(2, 5);
    cout<<t<<endl;
    while(t--){
        int n = rand(10, 100);
        int m = rand(10, 100);
        cout<<n<<" "<<m<<endl;
        for(int i= 0;i<m;i++){
            int type = rand(1,2);
            int u = rand(1,n);
            int v = rand(1,n);
            while(v==u)v = rand(1,n);
            cout<<type<<" "<<u<<" "<<v<<endl;
        }
    }


}

