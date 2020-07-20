#include <iostream>
#include <regex>
using namespace std;

// call as `./grammar < team.out`

// corresponding checktestdata grammar:
/*
WHILEI(i,MATCH("1234567890"))
    INT(0,499,a[i]) SPACE INT(0,499,b[i]) NEWLINE
END
EOF
*/

const int AC = 42, WA = 43;

int main() {
	regex line_regex{"[0-9]{1,3} [0-9]{1,3}"};
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
