#include<bits/stdc++.h>

using namespace std;

int difers(string s){
	char ult=s[s.length()-1];
	int dif=0;
	for(int i=0; i<s.length();i++){
		if(s[i]!=ult) 
			dif++;
		ult=s[i];
	}
	return dif;		
}

int main(){
	int N;
	string s1,s2;
	cin>>N>>s1>>s2;
	int dif1=difers(s1);
	int dif2=difers(s2);
	if(dif1>dif2)
	 cout<<"yes\n";
	else if(dif1<dif2)
	 cout<<"no\n";
	else if(dif1!=0 and dif1!=N){
		cout<<"yes\n";
	}else 
		cout<<"no\n";
	return 0;
}