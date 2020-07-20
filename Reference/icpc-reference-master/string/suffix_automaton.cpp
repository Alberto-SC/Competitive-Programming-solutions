using vi = int[26];
int cmpCh(char c){ return c-'a'; }

class sufAuto{
	const uint v0 = 1;
	struct Tvert{
		vi c;
		int suf=0, len=0;
	};
	int& suf(int vert){ return verts[vert].suf; }
	int& len(int vert){ return verts[vert].len; }
	// void fim(int vert){ if(vert > 0)finals.insert(vert),fim(suf(vert)); }
	vi& ch(int vert){ return verts[vert].c; }
public:
	uint cnt=0, v1=1, last=1, sz=1;
	vector<Tvert> verts;
	sufAuto(){}
	sufAuto(const string &s){ addStr(s); }
	void addStr(const string &s){
		uint n = s.size();
		sz += 2*n;
		verts.resize(sz);

		uint v2=0, v3=0, v4=0, v5=0, c;
		FOR(i,0,n){
			c = cmpCh(s[i]);
			v2 = ++last;
			len(v2) = len(v1) + 1;
			for(v3 = v1;v3 && !ch(v3)[c];){
				ch(v3)[c] = v2;
				v3 = suf(v3);
			}
			if(!v3){
				suf(v2) = v0;
				v1 = v2;
				continue;
			}
			v4 = ch(v3)[c];
			if(len(v4) == len(v3)+1){
				suf(v2) = v4;
				v1 = v2;
				continue;
			}
			v5 = ++last;
			verts[v5] = verts[v4];
			len(v5) = len(v3)+1;
			suf(v2) = v5;
			suf(v4) = v5;
			while(ch(v3)[c] == v4){
				ch(v3)[c] = v5;
				v3 = suf(v3);
			}
			v1 = v2;
		}
	}
	bool hasSubstr(const string &s){
		if(last==1) return false;
		int vert=v0;
		for(char c : s){
			vert = verts[vert].c[cmpCh(c)];
			if(!vert) return false;
		}
		return true;
	}
};

char s[100010];
int main(){
	char c;
	sufAuto sa;

	while(scanf(" %c %s",&c,s) == 2){
		for(int i = 0; s[i]; i++) s[i] = tolower(s[i]);
		if(c == 'A') sa.addStr(s);
		else{
			if(sa.hasSubstr(s)) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}