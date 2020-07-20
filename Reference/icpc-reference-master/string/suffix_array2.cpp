#include<bits/stdc++.h>

using namespace std;

using ll = unsigned long long;
using ii = pair<int, int>;
using iii = pair<ii, int>;
#define ff first
#define ss second
#define rk1 ff.ff
#define rk2 ff.ss

unsigned int f(char c){
	if(c >= 'a') return c - 'a';
	else return c - 'A' + 26;
}
char s[200005];
unsigned int n;
int SA[200005];
int ISA[200005];
int lcp[200005];

void build_sa(){
	int s2[200005];
	iii ord[200005];
	for(int i = 0; i < n; i++){
		s2[i] = f(s[i]);
		ord[i].rk1 = f(s[i]);
		ord[i].rk2 = i < n-1 ? f(s[i+1]) : -1;
		ord[i].ss = i;
	}
	sort(ord, ord+n);

	for(int k = 2; k <= n; k *= 2){
		int ant1, ant2;
		ant1 = ord[0].rk1;
		ant2 = ord[0].rk2;
		ord[0].rk1 = 0;
		for(int i = 1; i < n; i++){
			if(ant1 == ord[i].rk1 && ant2 == ord[i].rk2){
				ant1 = ord[i].rk1;
				ant2 = ord[i].rk2;
				ord[i].rk1 = ord[i-1].rk1; 
			}
			else{
				ant1 = ord[i].rk1;
				ant2 = ord[i].rk2;
				ord[i].rk1 = ord[i-1].rk1 + 1; 
			}
		}
		for(int i = 0; i < n; i++)
			s2[ord[i].ss] = ord[i].rk1;
		for(int i = 0; i < n; i++){
			if(ord[i].ss + k >= n)
				ord[i].rk2 = -1;
			else	
				ord[i].rk2 = s2[ord[i].ss + k];
		}
		sort(ord, ord + n);
	}
	for(int i = 0 ; i < n; i++){
		SA[i] = ord[i].ss;
		ISA[SA[i]] = i;
	}
}

void build_lcp(){
	int ini = 0;
	for(int i = 0; i < n; i++){
		if(ISA[i] + 1 >= n){
			lcp[ISA[i]] = 0;
			ini = 0;
			continue;
		}
		int j = ini + i;
		int k = ini + SA[ISA[i] + 1];
		while(k <= n-1 && j <= n-1 && s[j] == s[k]){
			j++;
			k++;
		}
		lcp[ISA[i]] = j - i;
		ini = max(lcp[ISA[i]] - 1, 0);
	}
}
