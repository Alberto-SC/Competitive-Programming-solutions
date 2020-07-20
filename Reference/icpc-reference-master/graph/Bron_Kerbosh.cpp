ll adj[70];
vector<ll> res; // cliques

void bron_kerbosh(ll r, ll p, ll e){
	if(!p and !e){
		res.push_back(r);
		return;
	}
	for(int i = 0; i < 64; i++){
		if(!(p & (1LL << i))) continue;
		bron_kerbosh(r | 1LL << i, p & adj[i], e & adj[i]);
		p ^= 1LL << i;
		e |= 1LL << i;
	}
}
