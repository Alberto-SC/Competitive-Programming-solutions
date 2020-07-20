void trieza(string s,int id){
	int et = 1,n = s.size();
	for(int i = 0; i < n; i++){
		if(trie[et][s[i] - 'a'] == 0)
			trie[et][s[i] - 'a'] = at++;
		et = trie[et][s[i] - 'a'];
	}

	final[et] = id;
}

void aho(){
	queue<pair<int,int>> q;
	q.push(mp(1,-1));
	while(!q.empty()){
		int v = q.front().ff;
		int l = q.front().ss;
		q.pop();
		for(int i = 0; i < 26; i++){
			if(trie[v][i]){
				pai[trie[v][i]] = v;
				q.push(mp(trie[v][i],i));
			}
		}

		if(erro[v] != -1){
			int a = erro[pai[v]];
			while(!erro[v]){
				if(a == -1)
					erro[v] = 1;
				else if(trie[a][l])
					erro[v] = trie[a][l];
				a = erro[a];
			}
		}
		if(acerto[v] != -1)
			acerto[v] = final[erro[v]] ? erro[v] : acerto[erro[v]];
	}
}

int ton(int estado, int c){
	while(!trie[estado][c - 'a']){
		estado = erro[estado];
		if(estado == -1){
			estado = 1;
			break;
		}
	}

	if(trie[estado][c - 'a'])
		estado = trie[estado][c - 'a'];
	
	return estado;
}

void corasick(string t,int id){
	int n = t.size(),et = 1,ac;
	for(int i = 0; i < n; i++){

		et = ton(et,t[i]);
	
		ac = et;
		while(ac != -1)
			ac = acerto[ac];
	}
}

