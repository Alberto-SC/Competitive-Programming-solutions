#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int n[15]={1,1};
int a[15]; 
double p,q;
int main()
{
    for(int i=2;i<10;i++)
    {
        n[i]=n[i-1]*i;
    }
    int T;
    cin>>T;
    while(T--)
    {
        char s[11];
        int cnt=0;
        scanf("%s",s);
        int l=strlen(s);
        for(int i=0;i<l;i++)
        {
            a[i]=s[i]-'0';
        }
        while(next_permutation(a,a+l))
        {
            cnt++;
        }
        cout<<cnt<<endl;
        if(cnt==0)
        {
            printf("0.000000000\n");
        }
        else
        {
            double temp=1.0/n[l];
            q=p=temp;
            for(int i=1;i<cnt;i++)
            {
                q=p+p*temp;
                p=q;
            }
            printf("%.9lf\n",p);
        }       
    }
    return 0;
}
