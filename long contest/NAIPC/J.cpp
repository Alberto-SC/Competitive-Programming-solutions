#include <bits/stdc++.h>
using namespace std;
int main(){
    string A,B;
    cin>>A>>B;
    int n = B.size();
    int cont = 0,last,first = 0,first2 =0;
    long long ans = 0;
    last = -1;
    bool y = true;
    for(int i = 0;i<A.size();i++){
        cout<<"Indice "<<i<<" "<<cont<<endl;
        if((cont == B.size()-1 && B.size()>1 )|| (cont == B.size() && B.size()== 1 )){
            cout<<"I "<<i<<" Last: "<<last<<" first: "<<first<<" first2: "<<first2<<endl;
            ans += (A.size()-i)+ ((A.size()-i)*(first-(last+1)));
            cout<<"ANS ="<<ans<<endl;
            if(first2!= 0)
            i = first2;
            y = true;
            cont = 0;
            last = first;
        }
        if(A[i] == B[cont]){
            if(cont == 0 ){first = i;cont++;continue;}
            cont++;
        }
        if(y&& cont){
            if(A[i]== B[0]){
                first2= i;
                 y = false;
                 }
        }
    }
    cout<<ans<<endl;

    return 0;
}