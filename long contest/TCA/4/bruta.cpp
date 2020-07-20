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
        vector<int> victory((r-l)+1);
        for(int j = l;j<=r;j++){
            for(int k = j+1;k<=r;k++){
                if(nums[j]%nums[k] == 0){
                    victory[k-l]++;
                }
                if(nums[k]%nums[j]== 0){
                    victory[j-l]++;
                }
            }
        }
        
        int ans = 0;
        for(auto c:victory){
            // cout<<c<<" ";
            if(c!= (r-l))ans++;
        }
        // cout<<endl;
        cout<<ans<<endl;
    }
    return 0;
}