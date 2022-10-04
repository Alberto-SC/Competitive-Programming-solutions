#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long 
#define __ ios_base::sync_with_stdio(false);cin.tie(NULL);


signed main(){__
	int t= 1,n;
    cin>>t;
    string a,s;
    while(t--){
        cin>>a>>s;
        string b;
        int idxa = a.size()-1;
        int idxs = s.size()-1;
        bool flag = true;
        while(idxa>=0 && idxs>=0){
            int ds = s[idxs]-'0',da = a[idxa]-'0';
            int ds2 = -1;
            if(idxs-1>=0)
                ds2 = ((s[idxs-1]-'0')*10)+(s[idxs]-'0');
            if(ds>=da){
                b+=to_string(ds-da);
                idxa--;
                idxs--;
            }
            else if(ds2 ==-1 ||(da+9)<ds2){
                flag = false;
                break;
            }
            else{
                b+=to_string(ds2-da);
                if(ds2<10){
                    flag = false;
                    break;
                }
                idxs-=2;
                idxa--;
            }
        }
        while(idxs>=0){ 
            b+=s[idxs--];
        }
        if(idxa>=0)flag = false;
        reverse(b.begin(),b.end());
        if(flag){
            int idx0= 0;
            while(b[idx0]=='0')idx0++;
            if(idx0==b.size())cout<<0<<endl;
            else{
                for(int i = idx0;i<b.size();i++)
                    cout<<b[i];
                cout<<endl;
            }
        }
        else 
            cout<<-1<<endl;
    }
    return 0;
}  
//        7543754
//         347534
//       88101288