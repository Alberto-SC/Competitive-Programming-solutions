#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _FORTIFY_SOURCE 2
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef long long int lli;

vector<lli> p_function(const string &v){
    lli n = v.size();
    vector<lli> p(n);
    for(lli i = 1;i<n;i++){
        lli j = p[i-1];
        while(j>0 && v[j]!= v[i]){
            j = p[j-1];
        }
        if(v[j] == v[i])
            j++;
        p[i] = j;
    }
    return p;
}
int main(){
    lli n,m,t;
    char l;
    cin>>n>>m;
    vector<pair<lli,char>> blocksa(n);
    vector<pair<lli,char>> blocksb(m);
    for(lli i = 0;i<n;i++){
        string x;
        cin>>x;
        lli j;
        for(j = 0;j<x.size();j++){
            if(x[j]== '-')break;
        }
        lli num = stoi(x.substr(0,j));
        l = x.back();
        blocksa[i] = {num,l};
    }
    for(lli i = 0;i<m;i++){
        string x;
        cin>>x;
        lli j;
        for(j = 0;j<x.size();j++){
            if(x[j]== '-')break;
        }
        lli num = stoi(x.substr(0,j));
        l = x.back();
        blocksb[i] = {num,l};
    }
    string s;
    string st;
    vector<pair<lli,char>> compressedA;
    vector<pair<lli,char>> compressedB;
    for(lli i = 0;i<n;){
        lli j = i;
        t = blocksa[j].x;
        while(j+1<n && blocksa[j].y ==blocksa[j+1].y){
            j++;
            t+= blocksa[j].x;
        } 
        char letter;
        if(j == i)letter = blocksa[j++].y;
        else letter = blocksa[++j-1].y;
        i = j;
        compressedA.push_back({t,letter});
    }
    for(lli i = 0;i<m;){
        lli j = i;
        t = blocksb[j].x;
        while(j+1<m && blocksb[j].y ==blocksb[j+1].y){
            j++;
            t+= blocksb[j].x;
        } 
        char letter;
        if(j == i)letter = blocksb[j++].y;
        else letter = blocksb[++j-1].y;
        i = j;
        compressedB.push_back({t,letter});
    }
    vector<lli> pos;    
    for(lli i = 0;i<compressedA.size();i++){
        string xx = to_string(compressedA[i].first)+compressedA[i].second;    
        // vector<lli> z(x.size(),i);
        for(lli j = 0;j<xx.size();j++)
            pos.push_back(i);
        s += xx;
        // cout<<c.first<<" "<<c.second<<endl;
    }
    n = compressedA.size();
    m = compressedB.size();
    if(m<=2){
        lli cont = 0;
        if(m == 1){
            for(lli i = 0;i<n;i++)
                if(compressedA[i].y == compressedB[0].y && compressedA[i].x>= compressedB[0].x)cont+=(compressedA[i].x-compressedB[0].x)+1;            
        }
        else {
            for(lli i = 0;i<n-1;i++){
                if(compressedA[i].y == compressedB[0].y && compressedA[i].x>= compressedB[0].x
                && compressedA[i+1].y == compressedB[1].y && compressedA[i+1].x>=compressedB[1].x)cont++;
            }
        }
        return cout<<cont<<endl,0;
    }  
    for(lli i = 1;i<m-1;i++){
        st+= to_string(compressedB[i].first)+compressedB[i].second;    
    }
    string  match = st+"$"+s;
    vector<lli> p = p_function(match);
    lli cont = 0;
    // cout<<n<<" "<<m<<" "<<pos.size()<<endl;
    for(int i = st.size()+1;i<match.size();i++){
        if(p[i]== st.size()){
            // cout<<i-(int)(st.size()+1)-(int)st.size()<<endl;
            // cout<<pos[i-(int)(st.size()+1)-(int)st.size()]<<endl;
            // cout<<i-(st.size()+1)+1<<endl;
            // cout<<pos[i-(st.size()+1)+1]<<endl;
            if(i-(int)(st.size()+1)-(int)st.size()>=0 &&compressedA[pos[i-(int)(st.size()+1)-(int)st.size()]].y == compressedB[0].y && 
            compressedA[pos[i-(int)(st.size()+1)-(int)st.size()]].x >= compressedB[0].x){
                // cout<<"YES"<<endl;
                if(i-(st.size()+1)+1<pos.size() && compressedA[pos[i-(st.size()+1)+1]]. y == compressedB.back().y && 
                    compressedA[pos[i-(st.size()+1)+1]].x >= compressedB.back().x)
                    cont++;
            
            }
            
        }
    }
    cout<<cont<<endl;
    return 0;

}