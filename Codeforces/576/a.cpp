#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,x,y;
    cin>>n>>x>>y;
    vector<int> nums(n);
    for(int i = 0;i<n;i++)
        cin>>nums[i];
    int pos = 0;
    for(int i =0;i<n-1;i++){
        int contx = 0,conty = 0;
        while(nums[i+1]<=nums[i] && i<n){i++;contx++;}
        if(contx>=x){
            pos = i+1;   
            if(i==n)cout<<n<<endl;
            else{
                while(nums[i+1]>=nums[i]){i++;conty++;}
                if(conty>=y){cout<<pos<<endl;break;}
            }
        }
        else{
            while(nums[i+1]>=nums[i]){i++;}
        }
    }
    return 0;
}