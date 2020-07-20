typedef complex < double > base ;

// y[i] = A(w^(dir*i)),
// w = exp(2pi/N) is N-th complex principal root of unity,
// A(x) = a[0] + a[1] x + ... + a[n-1] x^{n-1},
// * N must be a power of 2,
long double PI = 2 * acos(0.0L);


void fft ( vector < base > & a, bool invert )
{
	int n = ( int ) a. size ( ) ;

	for ( int i = 1 , j = 0 ; i < n ; ++ i ) {
		int bit = n >> 1 ;
		for ( ; j >= bit ; bit >>= 1 )	j -= bit ;
		j += bit;
		if ( i < j )swap ( a [ i ] , a [ j ] ) ;
	}
	for ( int len = 2 ; len <= n ; len <<= 1 )
	{
		double ang = 2 * PI / len * ( invert ? - 1 : 1 ) ;
		base wlen ( cos ( ang ) , sin ( ang ) ) ;

		for ( int i = 0 ; i < n ; i += len )
		{
			base w(1);
			for ( int j = 0 ; j < len / 2 ; ++j )
			{
				base u = a [i+j],v = a[i+j+len / 2 ] * w ;
				a [ i + j ] = u + v ;
				a [ i + j + len / 2 ] = u - v ;
				w *= wlen ;
			}
		}
	}
	if (invert)
		for ( int i = 0 ; i < n ; ++i )
			a [ i ] /= n ;
}


void convolve(const vector <int> &a, const vector <int> &b, vector
<int> &res)
{
	vector < base > fa ( a. begin ( ) , a. end ( ) ) , fb (
			b. begin ( ) , b. end ( ) ) ;
	size_t n = 1 ;
	while ( n < max ( a. size ( ) , b. size ( ) ) ) n <<= 1 ;
	n <<= 1 ;
	fa. resize ( n ) , fb. resize ( n ) ;
	fft ( fa, false ) , fft ( fb, false ) ;
	for ( size_t i = 0 ; i < n ; ++i )
		fa [ i ] *= fb [ i ] ;
	fft ( fa, true ) ;
	res. resize ( n ) ;
	for ( size_t i = 0 ; i < n ; ++i )
		res [ i ] = int ( fa [i].real( ) + 0.5 );}

void print(vector<int> a)
{
	cout << a.size()<<endl;
	for(int i = 0; i < (int)a.size(); ++i)
		cout << a[i] << " ";
	cout << endl;
}