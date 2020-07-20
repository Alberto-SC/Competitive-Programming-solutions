void sieveMaxPrime(vector<int>& lp, int n) {
    lp.resize(n+1, -1);

	int i;
	for(i = 2; i <= n; i++)
		if(lp[i] == -1){
			for(int j = i; j <= n; j += i) lp[j] = i;
		}
}