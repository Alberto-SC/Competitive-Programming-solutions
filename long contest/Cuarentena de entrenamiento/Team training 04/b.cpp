#include <bits/stdc++.h>
using namespace std;
int poly[100];

int main(){
    string s;
    cin>>s;
    bool sign = true;
    int i = 0;
    if(s[i]== '-')
        sign = false,i++;
    bool x = false;
    for(;i<s.size();){
        string coef= "",degree = "";
        while(i<s.size() && s[i]!= 'x'){
            coef+=s[i];
            i++;
        }
        if(s[i]== 'x')x = true;
        if(i == s.size()){
            if(coef.size()==0)break;
            else poly[0] = stoi(coef);
            break;
        }
        i++;
        while(i<s.size() && s[i]!= '-' && s[i]!= '+'){
            degree+=s[i];
            i++;
        }

        int d;
        if(degree.size()== 0)d =1;
        else d = stoi(degree);
        int c;
        if(coef.size()== 0)c = 1;
        else c = stoi(coef);
        if(!sign)c*=-1;
        if(s[i]== '+')sign = true;
        else sign = false;
        poly[d]  = c;
        i++;
    }

    bool first = true;
    for(int i = 99;i>0;i--){
        if(poly[i]!= 0){
            int c = poly[i]*i;
            if(first){
                if(i-1 > 1){
                    if(c == 1)cout<<"x"<<i-1;
                    else cout<<c<<"x"<<i-1; 
                }
                else if((i-1)==1){
                    if(c == 1)cout<<"x";
                    else cout<<c<<"x";
                }
                else if(i == 1)
                    cout<<c;
            }
            else {
                if(c>0){{
                    if(i-1 > 1)
                    cout<<"+"<<c<<"x"<<i-1;
                    else if((i-1) == 1) cout<<"+"<<c<<"x";
                    else if(i == 1)cout<<"+"<<c;
                }
                }
                else {
                    if(i-1> 1)
                    cout<<c<<"x"<<i-1;
                    else if((i-1)== 1)cout<<c<<"x";
                    else if(i == 1)
                        cout<<c;
                }
            }
            first = false;
        }

    }
    if(x == false)cout<<0;
    cout<<endl;

    return 0;
}