#include <bits/stdc++.h>
using namespace std;
const int N=1000000,INF=1000000000;
string a;
int t[N][26],l[N],r[N],p[N],sl[N],tv,tp,ts,la;

void ukkadd (int c) {
    // cout<<(char)(c+97)<<endl;
    suff:;
    // cout<<"TV "<<tv<<" TP "<<tp<<endl;
    if (r[tv]<tp) {
        // cout<<"ENTER"<<endl;
        if (t[tv][c]==-1) {
            // cout<<"ENTER 2"<<endl;
            t[tv][c]=ts;  l[ts]=la;
            // cout<<"NODE "<<t[tv][c]<<endl;
            p[ts++]=tv;  tv=sl[tv];  tp=r[tv]+1; 
            // cout<<"New tv "<<tv<<endl;
            goto suff; 
        }
        tv=t[tv][c]; tp=l[tv];
    }
    if (tp==-1 || c==a[tp]-'a') tp++; else {
        l[ts+1]=la;  p[ts+1]=ts;
        l[ts]=l[tv];  r[ts]=tp-1;  p[ts]=p[tv];  t[ts][c]=ts+1;  t[ts][a[tp]-'a']=tv;
        l[tv]=tp;  p[tv]=ts;  t[p[ts]][a[l[ts]]-'a']=ts;  ts+=2;
        tv=sl[p[ts-2]];  tp=l[ts-2];
        while (tp<=r[ts-2]) {  tv=t[tv][a[tp]-'a'];  tp+=r[tv]-l[tv]+1;}
        if (tp==r[ts-2]+1)  sl[ts-2]=tv;  else sl[ts-2]=ts; 
        tp=r[tv]-(tp-r[ts-2])+2;  goto suff;
    }
}

void build() {
    ts=2;
    tv=0;
    tp=0;
    fill(r,r+N,(int)a.size()-1);
    sl[0]=1;
    l[0]=-1;
    r[0]=-1;
    l[1]=-1;
    r[1]=-1;
    memset (t, -1, sizeof t);
    fill(t[1],t[1]+26,0);
    // for(int i = 0;i<20;i++){
    //     for(int j = 0;j<26;j++){
    //         cout<<t[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    for (la=0; la<(int)a.size(); ++la)
        ukkadd (a[la]-'a');
    // for(int i = 0;i<20;i++){
    //     for(int j = 0;j<26;j++){
    //         cout<<t[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}
int main(){
    clock_t begin = clock();
    cin>>a;
    build();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<fixed<<setprecision(6)<<time_spent<<endl;
    return 0;
}
// abcabcdabh