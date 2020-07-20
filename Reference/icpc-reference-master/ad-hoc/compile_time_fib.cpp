template<ul N>
struct fibonacci : integral_constant<ul, (fibonacci<N-1>{} + fibonacci<N-2>{})> {};
template<> struct fibonacci<1> : integral_constant<ul,1> {};
template<> struct fibonacci<0> : integral_constant<ul,0> {};
#define F0(x) fib[x]=fibonacci<x>{}
