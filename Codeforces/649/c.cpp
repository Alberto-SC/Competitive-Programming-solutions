#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int lli;
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);

int main(){__
    int n;
    cin>>n;
    vector<int> nums(n);
    for(auto &c:nums)cin>>c;
    bool flag = true;
    for(int i = 0;i<n;i++)
        if(nums[i]> i+1)flag = false;
    if(!flag)return cout<<-1<<endl,0;
    vector<int> b(n,n+1);
    vector<int> first(n+1,-1);
    vector<int> lastt(n+1,-1);
    for(int i = 0;i<n;i++){
        if(first[nums[i]] == -1)
            first[nums[i]] = i;
        lastt[nums[i]] = i;
    }
    int last = 0,lastp = 1,falta=-1;
    if(nums[0] == 1)falta = 1,b[0] = 0,last = 1;
    else falta = 0,b[0] = 1;
    for(int i = 1;i<n+1;i++){
        if(first[i]== -1)continue;
        for(int j = lastp;j<=first[i];j++){
            
            if(last == nums[j])last++;
            if(last == i)last++;
            b[j] =last++; 
        }
        if(falta!= -1 && i!= 0 && i != 1)
        b[first[i]] = falta,falta =-1;
        lastp = first[i];
    }
    set<int> st;
    for(auto c:b)st.insert(c);
    for(int i = 0;i<n;i++){
        if(lastt[i] != -1 && lastt[i]+1<n && st.find(i)==st.end())b[lastt[i]+1] = i;
    }
    for(auto c:b)cout<<c<<" ";
    cout<<endl;
    return 0;
}