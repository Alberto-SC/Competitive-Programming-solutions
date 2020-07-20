#include <unordered_map>/*{{{*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <locale>
#include <vector>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;/*}}}*/

enum JudgeCode:int{
  judge_error=1,
  correct=42,
  wrong_answer=43,
};

struct Edge{
  int a,b;
  long long weight;
};

struct TestCase{
  vector<Edge> edges;
  vector<long long> radii;
  int const n()const{return radii.size();}
};

TestCase read_input(ifstream &fin){
  TestCase t;

  int n; fin>>n;
  t.radii.resize(n);
  for (auto &i: t.radii) fin>>i;

  int m; fin>>m;
  t.edges.resize(m);
  for (auto &i: t.edges) fin>>i.a>>i.b>>i.weight, --i.a, --i.b;

  return t;
}

struct Solution{
  bool valid=false;
  bool possible=false;
  vector<int> assigned;

  explicit Solution(bool valid,bool possible): valid(valid), possible(possible){}
};

Solution read_output(basic_istream<char> &in, int const n){
  vector<string> tokens;
  for (string s; in>>s;){
    if (tokens.size()>=n){
      cerr<<"Warning: too many tokens. Ignoring the rest."<<endl;
      break;
    }
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    tokens.push_back(s);
  }

  // Impossible.
  if (tokens.size()>=1 and tokens[0]=="impossible"){
    return Solution{true, false};
  }

  // Possible.
  if (tokens.size()!=n){
    cout<<"Wrong number of tokens: expected "<<n<<" received "<<tokens.size()<<endl;
    return Solution{false, false};
  }

  Solution sol=Solution{true, true};
  set<int> seen;
  for (auto i: tokens){
    stringstream sst(i); int x; sst>>x;
    if (x<1 or x>n){
      cout<<"Permutation member out of bounds: 0 < "<<x<<" < "<<n<<endl;
      sol.valid=false;
    }
    if (not seen.insert(x).second){
      cout<<"Permutation member repeated: "<<x<<endl;
      sol.valid=false;
    }
    sol.assigned.push_back(x);
  }
  return sol;
}

bool check_assignment(Solution const &sol, TestCase const &test){
  for (Edge const edge : test.edges){
    auto const width
        = test.radii[sol.assigned[edge.a]-1]
        + test.radii[sol.assigned[edge.b]-1];
    if (width != edge.weight){
      cout<<"Width of edge "<<edge.a+1<<" "<<edge.b+1
          <<" is "<<width<<" not "<<edge.weight<<endl;
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv){
  if (argc<3){/*{{{*/
    cerr<<"usage: "<<argv[0]<<" testcase.in testcase.ans [feedback_dir] < team.out"<<endl;
    return judge_error;
  }else if (argc<4){
    cerr<<"writing feedback to stdout"<<endl;
  }else{
    if (argc>4){
      cerr<<"warning: ignoring "<<argc-4<<" extra arguments"<<endl;
    }
    if (not freopen((string(argv[3]) + "/judgemessage.txt").c_str(), "a", stdout)){
      cerr<<"unable to open feedback file for appending"<<endl;
      return judge_error;
    }
  }/*}}}*/

  ifstream canonical_input(argv[1]);
  ifstream canonical_output(argv[2]);
  auto &team_output = cin;

  // Read test case.
  TestCase const test_case = read_input(canonical_input);

  // Read canonical answer.
  Solution const canonical = read_output(canonical_output, test_case.n());
  if (not canonical.valid){
    return judge_error;
  }
  if (canonical.possible and not check_assignment(canonical, test_case)){
    cout<<"Judge output fails to solve the test case"<<endl;
    return judge_error;
  }

  // Read team answer.
  Solution const team = read_output(team_output, test_case.n());
  if (not team.valid){
    return wrong_answer;
  }
  if (team.possible and not check_assignment(team, test_case)){
    cout<<"Team output fails to solve the test case"<<endl;
    return wrong_answer;
  }

  // OK, validate answer
  if (team.possible == canonical.possible){
    return correct;
  }
  else if (team.possible and not canonical.possible){
    cout<<"Team solved the test case but judge output is impossible"<<endl;
    return judge_error;
  }
  else{
    return wrong_answer;
  }
}
