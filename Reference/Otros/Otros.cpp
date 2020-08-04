#include <bits/stdc++.h>
#define FUNCTION(name,operator) inline void name(int &current, int candidate) {!(current operator candidate) ? current = candidate : false;}
#define io(v) cin>>v
#define toStr(str) #str
using namespace std;
default_random_engine generator;
uniform_real_distribution<double> distribution(0.0,1.0);

//--------------Randoms bien randoms-----------------
int gen_base(const int before, const int after) {
    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt_rand(seed);
    int base = uniform_int_distribution<int>(before+1, after)(mt_rand);
    return base % 2 == 0 ? base-1 : base;
}

int sum() { return 0; }
template<typename T, typename... Args>
T sum(T a, Args... args) { return a + sum(args...); }

#define x first
#define y second
template<class A, class B> ostream& operator << (ostream &out, pair<A, B> &a) {
	return out << "(" << a.x << ", " << a.y << ")";
}

template <typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
    o << "[";
    for(size_t i = 0; i < v.size(); i++) {
        o << v[i];
        if(i != v.size() - 1) {
            o << ", ";
        }
    }
    o << "]";
    return o;
}
int main(){
    freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    fclose(stdin);
	fclose(stdout);
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);  
    double x = 2.0,y = 1.0;
    // islessgreater is equivalent to (x<y)|| (x>y)
    cout<<islessgreater(x,a)<<endl;
    cout<<isgreaterequal(x,a)<<endl;
    iota(p.begin(),p.end(),0); // fills an array with sequence starts in third parameter
    clock_t begin = clock();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<fixed<<setprecision(6)<<time_spent<<endl;
	__builtin_popcount(x);
    1 << __builtin_ctz(x);
    1<< (32-__builtin_ctz(x-1));
	for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cout << a[i][j] << " \n"[j == m];

    cout << bitset<20>(n) << "\n";

}
//________________FOR PYTHON____________________//
template<typename T>
struct number_iterator : std::iterator<random_access_iterator_tag, T>{
	T v;
	number_iterator(T _v) : v(_v) {}
	operator T&(){return v;}
	T operator *() const {return v;}
};
template <typename T>
struct number_range {
	T b,e;
	number_range(T b, T e):b(b),e(e){}
	number_iterator<T> begin(){return b;}
	number_iterator<T> end(){return e;}
};
/* make_pair like functions for our range type */
template<typename T> number_range<T> range(T e) {return number_range<T>(0, e);}

//_______________ inclusive range______________
template<typename T> number_range<T> range(T b, T e) {return number_range<T>(b, e);}
//Now we can do something like:

for (auto i: range(1000))
    sum += i;
or
for (auto i: range(10, 20))
    cout << i << endl;
//_____________Binary search___________________//
int findSqrt(int n){
	int lb = lower_bound(number_iterator<int>(0), number_iterator<int>(n), 0,
		[&] (int value, int /* ignored */ ) {
			return value * value <= n;
		}
	);
	return lb - 1;
}
//C++17
template<typename... Args>
void readln(Args&... args){
    ((cin >> args), ...);
}

template<typename... Args>
void writeln(Args... args){
    ((cout << args << " "), ...);
}

int x;
double y;
readln(x, y); // enter 100 500.1234
writeln(x, "some string", y); // 100 some string 500.1234
//CLAMP///
//Returns x if it is in the interval [low, high] or, otherwise, the nearest value:

cout << clamp(7, 0,  10); //7
cout << clamp(7, 0,  5);  //5
cout << clamp(7, 10, 50); //10
//_________________SPLIT STRING_______________________//
vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });
    input_string.erase(new_end, input_string.end());
    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }
    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
//________________LCS(Longest Comon subsecuence)______________//
const int Nmax = 5007;
int dp[Nmax][Nmax];
int LCS(vector<int> a,vector<int>b){
    int n = a.size();
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            if(a[i-1] == b[j-1])dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[n][n];
}
// Lectura rapida
int nextInt() {
    int x = 0, p = 1;
    char c;
    do {
        c = getchar();
    } while (c <= 32);
    if (c == '-') {
        p = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * p;
}
// kadane 2D
int kadane(int* arr, int* start, 
           int* finish, int n)  {  
    int sum = 0, maxSum = INT_MIN, i;  
    *finish = -1;  
    int local_start = 0;  
    for (i = 0; i < n; ++i){  
        sum += arr[i];  
        if (sum < 0)  {  
            sum = 0;  
            local_start = i + 1;  
        }  
        else if (sum > maxSum)  {  
            maxSum = sum;  
            *start = local_start;  
            *finish = i;  
        }  
    }  
    if (*finish != -1)  
        return maxSum;  
    maxSum = arr[0];  
    *start = *finish = 0;  
    for (i = 1; i < n; i++)  {  
        if (arr[i] > maxSum)  {  
            maxSum = arr[i];  
            *start = *finish = i;  
        }  
    }  
    return maxSum;  
}  

int kadane(vector<int> &A){
    lli cur = 0,best = 0,
    ans;
    int n = A.size();
    for(int i = 0;i<n;i++){
        cur += A[i];
        best = min(best, cur);
        ans = max(ans, cur-best);
    }
    return ans;
}



int M[400][400];
int findMax(int r,int c){  
    int maxSum = INT_MIN, finalLeft, finalRight,  
                          finalTop, finalBottom;  
    cout<<"HH "<<maxSum<<endl;
    int left, right, i;  
    int temp[r], sum, start, finish;  
    for (left = 0; left < c; ++left){  
        memset(temp, 0, sizeof(temp));  
        for (right = left; right < c; ++right){  
            for (i = 0; i < r; ++i)  
                temp[i] += M[i][right];  
            sum = kadane(temp, &start, &finish, r);  
            if (sum > maxSum){  
                maxSum = sum;  
                finalLeft = left;  
                finalRight = right;  
                finalTop = start;  
                finalBottom = finish;  
            }  
        }  
    } 
    cout << "(Top, Left) (" << finalTop 
         << ", " << finalLeft << ")" << endl;  
    cout << "(Bottom, Right) (" << finalBottom  
         << ", " << finalRight << ")" << endl;  
    cout << "Max sum is: " << maxSum << endl;  
    return maxSum;   
}  
// Bynary search find the last that is possible
while(l<r){
    int m = (l+r+1)>>1;
    if(check(m))
        l = m;
    else r = m-1;
} 
// find the first that is possible
// is in r;

while(l<r){
    int mid = (l+r)>>1;
    if(check(mid,0) || check(mid,1));
        r = mid;
    else l = mid+1:
}
// ans is in l
/*----------------------Graph Moves----------------*/
const int fx[]={+1,-1,+0,+0};
const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
int n,m;    
bool valid(ll x, ll y) { return x >= 1 && x <= n && y >= 1 && y <= m; }
void dfs(int y,int x){
    int nx = x;
    int ny = y;
    for(int i = 0;i<4;i++){
        nx= x+fx[i];
        ny= y+fy[i];
        // cout<<nx<<" "<<ny<<endl;
        if(valid(nx,ny)  && grid[ny][nx] == '1' && !vis[ny][nx]){
            vis[ny][nx] = true;
            bfs(ny,nx);
        }
    }
}
/*------------------------------------------------*/
 
/*-----------------------Bitmask------------------*/
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/





// for a graph with one cycle A->B->C->D if you want to A*A = A*B ans B*B = B*C do this->
// #include <bits/stdc++.h>
// using namespace std;
// const double PI = acos(-1.0L);
// typedef long double ld;
// using comp = complex<long double>;
// int main(){
//     comp a,b2,a2;
//     ld ang1 = 2 * PI * 0/ 3;
//     ld ang2 = (PI - 2 * PI * 0) / 3;
//     a = comp(cosl(ang1), sinl(ang1));
//     a2 = comp(cosl(ang2), sinl(ang2));
//     ang1 = 2 * PI * 2 / 3;
//     ang2 = (PI - 2 * PI * 2) / 3;
//     b2 = comp(cosl(ang2),sinl(ang2));
//     cout<<a<<endl;
//     cout<<a2<<endl;
//     cout<<b2<<endl;
//     cout<<a*a2<<endl;
//     cout<<a*b2<<endl;
//     return 0;
// }
// Entrada y salida rápida 
int get(){
  char c;
  while(c=getchar(),(c<'0'||c>'9')&&(c!='-'));
  bool flag=(c=='-');
  if(flag)
    c=getchar();
  int x=0;
  while(c>='0'&&c<='9')
    {
      x=x*10+c-48;
      c=getchar();
    }
  return flag?-x:x;
}
 
void output(int x){
    if(x<0)
        {
        putchar('-');
        x=-x;
        }
    int len=0,data[10];
    while(x)
        {
        data[len++]=x%10;
        x/=10;
        }
    if(!len)
        data[len++]=0;
    while(len--)
        putchar(data[len]+48);
    putchar('\n');
}

// Make a png image to show graph 
// graph is an array of vectors vector<int> graph[n]
// you only need to install graphvis  with  sudo apt-get install graphviz and xdg to open automatically 
// this can be installed with sudo apt-get install -y xdg-utils then you only need to call show_graph in any program with a graph 

void show_graph(const bool undirected = true) {
    /*! Converts graph to dot format
     *\param undirected is whether graph is undirected or not */
	ofstream os{"graph.dot"};
	os << (undirected ? "graph" : "digraph");
	os << " G {" << endl;
	for(int u = 0; u < maxn; ++u) {
		for (const auto v : graph[u]) {
			if (!undirected || u <= v) {
				os << "\t" << u << (undirected ? " -- " : " -> ") << v << endl;
			}
		}
	}
	os << "}" << endl;
    /* Displays dot using image viewer
    / This command is for Linux. You can change this command for a different OS or for a different image viewer.*/
	system("dot -Tpng graph.dot -o graph.png && xdg-open graph.png");
}
