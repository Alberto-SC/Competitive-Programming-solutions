#include <iostream>
using namespace std;

int main(){
	string a;
	string b;
	int moda = 1,modb = 1;
	cin>>a;
	cin>>b;
	for(int i = 0;i<a.lenght();i++)
		moda *= (a[i]-'A')%47;
	moda %=47;
	for(int i = 0;i<b.lenght();i++)
		modb *= (b[i]-'A')%47;
	modb %=47;
	if(moda == modb)cout<<"GO";
	else cout<<"STAY";
}