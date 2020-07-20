#include<stdio.h>
#include<iostream>
#include <iomanip>
#include <cfenv>
using namespace std;
int main()

{

 double d=15.6464545347;

cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    std::fesetround(FE_DOWNWARD); 
	cout << d<< '\n'; 
 
	printf("%.2f\n", d);

}
