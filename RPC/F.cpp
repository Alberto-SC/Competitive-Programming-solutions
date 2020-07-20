#include <bits/stdc++.h>
using namespace std;
#define print(A) for(auto c:A)cout<<c<<" ";
int main(){
    string a;
    cin>>a;
    int len = a.size();
    int max = -100;
    vector<int> Frecuency(10,0);
    for(int i = 0;i<len;i++){
        Frecuency[a[i]-'0']++;
    }
    int mi = 1009,minin;

    for(int i = 0;i<10;i++){
        if(Frecuency[i]<mi){mi= Frecuency[i];minin= i;}
    }
    bool y = false;
    if(minin== 0){
        int i ;
        for(1;i<10;i++){ 
            if(Frecuency[i]!= 0)
            continue;
            else {
                y = true;
                break;   
            }
        }
        if(!y)
        cout<<"1";
        else {
            cout<<i<<endl;
            return 0;
        }
    }
    for(int i = 0;i<mi+1;i++)cout<<minin;
    return 0;
}