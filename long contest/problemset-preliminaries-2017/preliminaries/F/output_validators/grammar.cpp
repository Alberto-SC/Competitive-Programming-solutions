#include <iostream>
#include <regex>
using namespace std;

// call as `./grammar < team.out`

// corresponding checktestdata grammar:
/*
FLOAT SPACE FLOAT SPACE FLOAT NEWLINE
EOF
*/

const int AC = 42, WA = 43;

string float_regex = R"(-?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?)";

int main() {
	regex line_regex{float_regex + " " + float_regex + " " + float_regex};
	string line;
	while(getline(cin, line)) {
		if(!regex_match(line, line_regex)) {
			cout << "Line below doesn't match the regex!\n" << line << endl;
			return WA;
		}
	}
	if(!line.empty()) {
		cout << "last line wasn't empty! Maybe forgot the final newline?\n" << line << endl;
		return WA;
	}
	return AC;
}
