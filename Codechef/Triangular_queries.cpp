#include <iostream>
#include <vector>
using namespace std;
struct Punto{
	int x,int y;
	Punto():{}
	Punto(int X, int Y):x(X), y(Y){}
	bool operator<(const Punto& q){
		if(x != q.x) return x<q.x;
		return y== ?q.y? false:y<q.y;
	}
	Punto operator+(const Punto& q){return Punto(x+q.x,y+y.y);}
	Double Dot( const Punto& q ) const { return x*q.x + y*q.y; }
  	Double Cruz( const Punto& q ) const { return x*q.y - y*q.x; }	
};
int main(){
	vector<Punto>n Puntos;
	int x, y,n,q,d;
	cin<<n;
	for(int i = 0;i<n;i++){
		cin<<x<<y;
		Puntos.push_back(Punto(x,y);
	}
	sort(Puntos.begin(),Puntos.end());
	
}