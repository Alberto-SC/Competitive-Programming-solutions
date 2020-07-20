#include <iostream>
using namespace std;
#define printc(A)  for(auto a:A)cout<<c.real()<<" ";
const PI = acos(-1);
using comp = complex<long double>;
typedef vector<complex> vec;
#define Nozero(auto c) fabs(c.real)<1e-3
int lesspow(int n){
    int ans = 1;
    while(ans <n){
        ans<<=1;
    }
    return ans;
}
void fft(vec &a,int inv){
    int n = a.size();
	for(int i = 1,j = 0;i<n-1;i++){
		for(int k = n>>1;(j^= k) <k; k>>= 1);
			if(i<j) swap(a[i],a[j]);
	}
	for(int k = 1;k<n;k<<=1){
		comp wk = polar(1.0,PI/k*inv);
		for(int i = 0;i<n;i+= k<<1){
			comp w(1);
			for(int j = 0;j<k;j++,w = w*wk){
				comp t = a[i+j+k]*w;
				a[i+j+k] = a[i+j]-t;
				a[i+j] += t;
			}
		}
	}
	if(inv == -1)
		for(int i = 0;i<n;i++)
			a[i]/=n;


    
}
void multiplyPol(vec &A, vec&B){
    int n0 = A.size()+B.size()-1;
    int n = lesspow(n0);
    A.resize(n);
    B.resize(n);
    fft(A,1);
    fft(B,1);
    for(int i = 0;i<n;i++){
        A[i]*=B[i];
    }
    fft(A,-1);
    A.resize(n0);
}

void powPolynom(vec &A,int n){
    vec ans(1,1);
    vec tmp = A;
    while(n) {
        if(n&1) 
            multiplyPol(ans,tmp);
        n >>= 1;
        multiplyPol(tmp,tmp);
    }
    A = ans;
}



int main(){
    int nkind,value,ntake;
    cin>>nkind,ntake;
    vec Pol(1002);
    for(in t i = 0;i<nkind;i++){
        cin>>a;
        pol[a]= 1;
    }
    powPolynom(pol,ntake);
    for(int i = 0;i<pol.size();i++){
        if(!Nozero(pol[i]))cout<<i<<" ";
    }

    return 0;
}