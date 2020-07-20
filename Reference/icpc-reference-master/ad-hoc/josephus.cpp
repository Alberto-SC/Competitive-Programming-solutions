int f(int n, int k){	// #people, jump size
	return (n == 1) 1 : (f(n-1, k) + k - 1) % n + 1;
}
