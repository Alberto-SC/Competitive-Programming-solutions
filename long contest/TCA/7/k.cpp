#include <bits/stdc++.h>
using namespace std;
const int maxn = 100007;
vector<int> st[26];
vector<int> lazy[26];

void propagate(int v,int l,int r ,int letter){
    if(lazy[letter][v]== -1)return ;
    st[letter][v] = ((r-l)+1) *lazy[letter][v];
    if(l != r){
        lazy[letter][v<<1]= lazy[letter][v];
        lazy[letter][v<<1|1]= lazy[letter][v];
    }
    lazy[letter][v] = -1;
}

int n,m;
void update(int l,int r,int val,int letter,int v = 1,int sl = 0,int sr = n-1){
    propagate(v,sl,sr,letter);
    if(l>sr || r<sl || sl>sr)return ;
    if(sl>=l && sr<=r){
        lazy[letter][v] = val;
        propagate(v,sl,sr,letter);
        return ;
    }
    int mid = (sl+sr)>>1;
    update(l,r,val,letter,v<<1,sl,mid);
    update(l,r,val,letter,v<<1|1,mid+1,sr);
    st[letter][v] = st[letter][v<<1]+st[letter][v<<1|1];
}

int query(int l,int r,int letter,int v = 1,int sl = 0,int sr = n-1){
    propagate(v,sl,sr,letter);
    if(l>sr || r<sl || sl>sr)return 0;
    if(sl>=l && sr<=r)return st[letter][v];
    int mid = (sl+sr)>>1;
    return query(l,r,letter,v<<1,sl,mid)+query(l,r,letter,v<<1|1,mid+1,sr);
}


int main(){
    int l,r,type;
    cin>>n>>m;
    string s;
    cin>>s;
    for(int i = 0;i<26;i++){ 
        st[i] = vector<int> (4*maxn,0);
        lazy[i] = vector<int> (4*maxn,-1);
    }
    for(int i= 0;i<n;i++)
        update(i,i,1,s[i]-'a');
    
    for(int i = 0;i<m;i++){
        cin>>l>>r>>type;
        l--,r--;
        int ofs = 0;
        for(int j = 0;j<26;j++){
            int cuantos = query(l,r,j);
            if(l+ofs>r)break;
            if(cuantos == 0)continue;
            update(l,r,0,j);
            if(type){
                update(l+ofs,l+ofs+(cuantos-1),1,j);
            }
            else {
                update((r-ofs-cuantos)+1,r-ofs,1,j);
            }
            ofs+=cuantos;
        }
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<26;j++){
            if(query(i,i,j)){cout<<char(j+'a');break;}
        }
    }

    return 0;
}

// 10 5
// abacdabcda
// 1 10 0
// 1 10 0
// 1 10 0
// 1 10 0
// 1 10 0