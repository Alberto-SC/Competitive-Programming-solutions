#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
typedef long double Double;
const Double ERROR = 1e-9;

#define EQ(a, b) (fabs((a) - (b)) < ERROR)
struct Punto{
	int x,y;
	Punto(int X,int Y): x(X),y(Y){}
	bool operator<(const Punto& q){
		if(!EQ(x,q.x)) return x<q.x;
		return EQ(y,q.y)? false:y<q.y;
	}
	Punto operator-(const Punto& q)const {return Punto(x-q.x,y-q.y);}
	Double cruz(const Punto& q)const {return x*q.y - y*q.x;}
	Double abs()const{return hypot(x,y);}
	Double dist(const Punto& q)const {return(*this-q).abs();}
};
int orientation(const Punto& o,const Punto& p,const Punto& q){
	Double ccw = (p-o).cruz(q-o);
	return EQ(ccw,0)? 0:(ccw<0)? -1:1;
}

typedef vector<Punto> Poligono;

Poligono convexhull(Poligono p){
	int k = 0;
	int n = p.size();
	Poligono h(2*n,Punto(0,0));
	sort(p.begin(),p.end());
	for(int i = 0;i<p.size();i++){	
		while(k>= 2 && orientation(h[k-2] , h[k-1] , p[i])<= 0)k--;
		h[k++] = p[i];
	}
	int t;
	for(int i = n-1, t = k+1; i>0;--i){	
		while(k>=t && orientation(h[k-2] , h[k-1] , p[i-1])<= 0)k--;
		h[k++] = p[i-1];
	}
	return h;

}
Double rotating_calipers(Poligono p){
	Poligono convex = convexhull(p);
	int h = convex.size();
	int k = 1;
	while(fabs((convex[0]-convex[h-1]).cruz(convex[k+1]-convex[h-1])) > fabs((convex[0]-convex[h-1]).cruz(convex[k]-convex[h-1])))k++;
	long double res = 0;
	for (int i = 0, j = k; i <= k && j < h; ++i) {
        res = max(res, convex[i].dist(convex[j]));
        while (j < h && fabs ((convex[i+1]- convex[i]).cruz(convex[j+1]-convex[i]))  > fabs ((convex[i+1]- convex[i]).cruz(convex[j]-convex[i])) ){
            res = max(res, convex[i].dist(convex[(j + 1)]));
            ++j;
        }
    }

    return res;

}
int main(){
	int n,x,y;
	cin>>n;
	Poligono p;
	for(int i = 0;i<n;i++){
		cin>>x>>y;
		p.push_back(Punto(x,y));
	}
	cout << fixed;
	cout << setprecision(9);
	if(n == 2)cout<<p[0].dist(p[1]);
	else cout<<rotating_calipers(p);



}