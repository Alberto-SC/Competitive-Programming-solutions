// c, x, y -> a*x + b*y = c
tuple<ll, ll, ll> gcd_extended(ll a, ll b){
	if(a == 0) return make_tuple(b, 0, 1);

	ll c, x1, y1;
	tie(c, x1, y1) = gcd_extended(b%a, a);

	return make_tuple(c, y1 - (b/a)*x1, x1);
}