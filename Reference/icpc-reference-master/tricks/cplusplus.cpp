// lambda functions
sort(p, p+n, [=](int i, int j) { return p[i] < p[j]; });

string r_str =
R"Multi Line
String";
cout « r_str;

// define literals (0xA, 1000ll, 3.14f). They should start with _
// parameters only can be one of these:(const char *)(unsigned long long int)(long double)(char)(wchar_t)(char16_t)(char32_t)(const char *, size_t)(const wchar_t *, size_t)(const char16_t *, size_t)(const char32_t *, size_t)Literals also can used with templates. 
long long operator "" _km(unsigned long long literal) {
  return literal * 1000;
}
cout « 12_km « " meters \n"; // Prints 12000 meters

// define a any-type sum function:
int sum() { return 0; }

template<typename T, typename... Args>
T sum(T a, Args... args) { return a + sum(args...); }
cout « sum(5, 7, 2, 2) + sum(3.14, 4.89); /* prints "24.03" */ 

// Euclidean Algorithm - gcd of two numbers
__gcd(value1, value2)
// returns 1 + least significant 1-bit of x. If x == 0, returns 0. Here x is int, this function with suffix 'l' gets a long argument and with suffix 'll' gets a long long argument
__builtin_ffs(x)
// returns number of leading 0-bits of x which starts from most significant bit position. x is unsigned int and like previous function this function with suffix 'l gets a unsigned long argument and with suffix 'll' gets a unsigned long long argument. If x == 0, returns an undefined value
__builtin_clz(x)
// returns number of trailing 0-bits of x which starts from least significant bit position. x is unsigned int and like previous function this function with suffix 'l' gets a unsigned long argument and with suffix 'll' gets a unsigned long long argument. If x == 0, returns an undefined value
__builtin_ctz(x)
// returns number of 1-bits of x. x is unsigned int and like previous function this function with suffix 'l' gets a unsigned long argument and with suffix 'll' gets a unsigned long long argument. If x == 0, returns an undefined value
__builtin_popcount(x)
