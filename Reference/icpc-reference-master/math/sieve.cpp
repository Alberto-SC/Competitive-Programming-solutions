void sieveErathostenes(vector<int>& out, int n){
	vector<bool> v(n+1,false);
	out.push_back(2);
	int i;
	for(i = 3; i*i <= n; i += 2){
		if(!v[i]){
			out.push_back(i);
			for(int j = i*i; j <= n; j *= i)v[j] = true;
		}
	}
	for(;i <= n;i += 2)if(!v[i]) out.push_back(i);
}
