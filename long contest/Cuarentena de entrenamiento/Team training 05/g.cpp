#include<bits/stdc++.h>

using namespace std;

int main(){
	int Y;
	cin>>Y;
	int lastY = 2018;
	int lastM = 3;
	while(lastY<Y){
		lastM +=26;
		while(lastM>=12){
			lastY++;
			lastM-=12;
		}
	}
	if(lastY==Y)
		cout<<"yes\n";
	else
		cout<<"no\n";
	return 0;
}