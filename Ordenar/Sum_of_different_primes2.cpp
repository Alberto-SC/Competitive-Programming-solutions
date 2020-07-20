#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


vector<bool> numeros_primos(){
	vector<bool> boolprimes(2000,true);
	boolprimes[0] = false;
	boolprimes[1] = false;
	for(int i = 2;i<2000;i+= 2)boolprimes[i] =false;
	for(int i = 3;i<2000;i+= 2){
		if(boolprimes[i]){
			for(int j = i*i;j<2000;j+= 2*i)boolprimes[j] = false;
		}
	} 
	return boolprimes;
}
vector<long long> Vector_de_primos(const vector<bool> &BoolPrimes){         
        vector<long long > VectorOfPrimes;                       
        for (int i = 0; i <= 2000; ++i)             
            if (BoolPrimes[i] == true) VectorOfPrimes.push_back(i);      
        return VectorOfPrimes;                                               
    }
vector<long long> Primes = Vector_de_primos(numeros_primos());
#define N 2048
#define K 16
#define P 309
long long NumberOfWays[N][K][P];


long long sum_of_primes(int n,int k,int i){
	if(n == 0 && k == 0)return 1;
	if (n < 0 or k < 0 or Primes[i] > n or i ==P) return 0;
	if(NumberOfWays[n][k][i] != -1) return NumberOfWays[n][k][i];
	long long restandoprimos = sum_of_primes(n-Primes[i],k-1,i+1);
	long long probando_otro_primo = sum_of_primes(n,k,i+1);
	NumberOfWays[n][k][i] = restandoprimos + probando_otro_primo;
	return NumberOfWays[n][k][i];
}

int main(){
	int n,k;
	memset(NumberOfWays,-1,sizeof NumberOfWays);
	while(cin>>n>>k && (n|k)){
		cout<<sum_of_primes(n,k,0)<<endl;
	}
	return 0;
}