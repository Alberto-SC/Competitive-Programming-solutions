#include <bits/stdc++.h>
using namespace std;
struct Query{
    int x,y,k;
};

vector<int> st;
vector<int> lazy;
void propagate(int v,int l,int r){
    if(lazy[v]== 0)return;
    st[v] = lazy[v];
    if(l!= r){
        lazy[v<<1] = lazy[v];
        lazy[v<<1|1] = lazy[v];
    }   
    lazy[v] =0; 
}

void update(int v,int sl,int sr,int l,int r,int val){
    propagate(v,sl,sr);
    if(r<sl || l>sr || sl>sr)return ;
    if(sl>= l && sr<=r){
        lazy[v] = val;
        propagate(v,sl,sr);
        return;
    }
    int m = (sl+sr)>>1;
    update(v<<1,sl,m,l,r,val);
    update(v<<1|1,m+1,sr,l,r,val);
    st[v] = st[v<<1];
}

int  query(int v,int sl,int sr,int l,int r){
    // cout<<sl<<" "<<sr<<endl;
    propagate(v,sl,sr);
    if(r<sl || l>sr || sl>sr)return 0;
    if(sl>= l && sr<=r)return st[v];
    int m = (sl+sr)/2;
    return max(query(v<<1,sl,m,l,r),query(v<<1|1,m+1,sr,l,r));
}


int main(){
    int n,m,type,x,y,k;
    cin>>n>>m;
    st.resize(4*n);
    lazy.resize(4*n);
    vector<int> a(n);
    vector<int> b(n);
    for(auto &c: a)cin>>c;
    for(auto &c: b)cin>>c;
    vector<int> z(n,0);
    vector<Query> q;
    int cont = 1;
    for(int i = 0;i<m;i++){
        cin>>type;
        if(type == 1){
            cin>>x>>y>>k;
            x--,y--;
            update(1,0,n-1,y,y+k-1,cont);
            // cout<<"HI"<<endl;
            q.push_back({x,y,k});
            cont++;
        }
        else {
            cin>>x;
            x--;
            int idx = query(1,0,n-1,x,x);
            if(idx == 0)cout<<b[x]<<endl;
            else {
                cout<<a[q[idx-1].x+x-q[idx-1].y]<<endl; 
            }
        }
    }
    return 0;
}