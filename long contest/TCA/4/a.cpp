#include <bits/stdc++.h>
using namespace std;

vector<int> st;
int n,m;
void update(int pos ,int val ,int v = 1,int sl = 0,int sr = n-1){
    if(sl == sr  && sl == pos){
        st[v] = val;
        return;
    }
    int mid = (sl+sr)>>1;
    if(pos<=mid)update(pos,val,v<<1,sl,mid);
    else update(pos,val,v<<1|1,mid+1,sr);
    st[v] = __gcd(st[v<<1],st[v<<1|1]);
}

int query(int l,int r,int v= 1,int sl = 0,int sr = n-1){
    if(l>sr || r<sl || sl>sr)return 0;
    if(sl>=l && sr<=r)return st[v];
    int mid = (sl+sr)>>1;
    return __gcd(query(l,r,v<<1,sl,mid),query(l,r,v<<1|1,mid+1,sr));
}

int main(){
    int l,r;
    cin>>n;
    st.resize(4*n);
    vector<int> nums(n);
    for(auto &c:nums)cin>>c;
    map<int,int> mp;
    int key = 0;
    vector<int> fr[n];
    for(int i = 0;i<n;i++){
        update(i,nums[i]);
        if(!mp.count(nums[i])){
            mp[nums[i]]= key;
            fr[key++].push_back(i);
        }
        else fr[mp[nums[i]]].push_back(i);
    }
    cin>>m;
    for(int i= 0;i<m;i++){
        cin>>l>>r;
        l--,r--;
        int gcd = query(l,r);        
        // cout<<gcd<<endl;
        // if(l == r){cout<<1<<endl;continue;}
        if(!mp.count(gcd)){cout<<(r-l)+1<<endl;continue;}
        int idx = mp[gcd];
        int idxl = lower_bound(fr[idx].begin(),fr[idx].end(),l)-fr[idx].begin();
        int idxr = lower_bound(fr[idx].begin(),fr[idx].end(),r)-fr[idx].begin();
        // for(auto c:fr[idx])cout<<c<<" ";
        // cout<<endl;
        // cout<<idxl<<" "<<idxr<<endl;
        if(idxr<fr[idx].size() && fr[idx][idxr] == r)idxr++;
        // if(idxr != fr[gcd].size() && fr[gcd][idxr]== r)idxr++;
        int cuantos = idxr-idxl;
        // cout<<cuantos<<endl;
        cout<<((r-l)+1)-cuantos<<endl;
    }
    return 0;
}