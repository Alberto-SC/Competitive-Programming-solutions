#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <regex>
#include <locale>  
using namespace std;
int main ()
{
 locale loc;
  string s ;
  cin >> s;
  string F ="";
  for (string::size_type i=0; i<s.length(); ++i)
    tolower(s[i],loc);
  regex e ("a|o|e|u|i|y"); 
  s  = regex_replace (s,e,"");
  for(int i = 0;i<s.length();i++){
  	F += "."+s[i]; 
  }
  cout<<F; 
  return 0;

}
