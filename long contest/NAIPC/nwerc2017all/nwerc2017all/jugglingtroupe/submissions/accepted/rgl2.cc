#include <iostream>
#include <string>
using namespace std;

char s[1000002];
static int zero1[1000002], n1=1;
static int zero2[1000002], n2=1;

int main(){
  char *sp=s;
  size_t buffer_size=sizeof s;
  ssize_t const n=getline(&sp, &buffer_size, stdin)-1;
  s[n]=0;

  zero1[0]=-1, zero2[0]=n;
  for (auto i=n; i--;) if (s[i]=='0') zero2[n2++]=i;

  for (int i=0; i<n; i++){
    while (zero2[n2-1]<=i){
      zero1[n1++]=zero2[--n2];
    }
    while (s[i]>='2'){
      int pl=0;
      pl+=zero1[n1-1]-i; if (n1>1) s[zero1[--n1]]++;
      pl+=zero2[n2-1]-i; if (n2>1) s[zero2[--n2]]++;
      int a=min(i,i+pl), b=max(i,i+pl);
      if ('0'==--s[b]) zero2[n2++]=b;
      if ('0'==--s[a]) zero2[n2++]=a;
    }
  }
  puts(s);
}
