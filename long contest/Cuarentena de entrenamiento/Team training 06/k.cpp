using namespace std;
typedef  long long int lli;
const lli mod = 986424689;

lli multMod(lli a, lli b, lli n){
	lli ans = 0;
	a %= n, b %= n;
	if(abs(b) > abs(a)) swap(a, b);
	if(b < 0){
		a *= -1, b *= -1;
	}
	while(b){
		if(b & 1) ans = (ans + a) % n;
		b >>= 1;
		a = (a + a) % n;
	}
	return ans;
}


lli modularInverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(r0 < 0) s0 *= -1;
	if(s0 < 0) s0 += m;
	return s0;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	if(e < 0){
		b = modularInverse(b, m);
		e *= -1;
	}
	while(e){
		if(e & 1) ans = (ans * b) % m;
		e >>= 1;
		b = (b * b) % m;
	}
	return ans;
}

int main(){

    lli t,n,c,z;
    cin>>t;
    for(int i=0; i<t;i++){
        cin>>c>>n;
        if(c==1){
          lli x=multMod(n ,(n+1),mod);
          lli y = powerMod(2,mod-2,mod);
          z= multMod(x,y,mod);
        }else{
          lli x = powerMod(c,n+2,mod);
          x = multMod(x,n,mod);
          lli a = powerMod(c,n+1,mod);
          a =multMod(a,n+1,mod);
          z = (x-a)+c;
          if(z<0)z+=mod;
          z%=mod;
          lli b = powerMod(c-1,2,mod);
          lli y = powerMod(b,mod-2,mod);
          z = multMod(z,y,mod);
        }
        cout<<z;
        if(i!=t-1)cout<<"\n";
    }


    return 0;
}