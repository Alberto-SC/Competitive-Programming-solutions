#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
set<pair<int,string>> st;

int main(){
  st.insert({1,"."});
	st.insert({3,"-"});
	st.insert({3,".."});
	st.insert({5,".-"});
	st.insert({5,"-."});
	st.insert({7,"--"});
	st.insert({5,"..."});
	st.insert({7,"-.."});
	st.insert({7,".-."});
	st.insert({7,"..-"});
	st.insert({9,"--."});
	st.insert({9,".--"});
	st.insert({9,"-.-"});
	st.insert({11,"---"});
	st.insert({7,"...."});
	st.insert({9,"-..."});
	st.insert({9,".-.."});
	st.insert({9,"..-."});
	st.insert({9,"...-"});
	st.insert({11,"--.."});
	st.insert({11,".--."});
	st.insert({11,"..--"});
	st.insert({11,"-.-."});
	st.insert({11,"-..-"});
	st.insert({11,".-.-"});
	st.insert({13,"---."});
	st.insert({13,".---"});
	st.insert({13,"-.--"});
	st.insert({13,"--.-"});
	st.insert({15,"----"});
	st.insert({9,"....."});
    st.insert({11,"-...."});
    st.insert({11,".-..."});
    st.insert({11,"..-.."});
    st.insert({11,"...-."});
    st.insert({11,"....-"});
    
    string s;
    getline(cin,s);
    vector<int> b(52);
    lli ans = 0;
    for(int i = 0;i<s.size();i++){
        if(s[i]>= 'A' && s[i]<= 'Z')s[i]+=32;
        if(s[i]>= 'a' && s[i]<= 'z')b[s[i]-'a']++;
        if((s[i]>= 'a' && s[i]<= 'z'))ans+=3;    
    }
    ans-=3;
    sort(b.rbegin(),b.rend());
    auto it = st.begin();
    for(int i = 0;i<52;i++){
        if(b[i]== 0)break;
        ans+=(b[i]*it->first);
        // cout<<b[i]<<" -> "<<it->second<<" "<<it->first<<endl;
        it++;
    }
    cout<<ans<<endl;
    return 0;
}