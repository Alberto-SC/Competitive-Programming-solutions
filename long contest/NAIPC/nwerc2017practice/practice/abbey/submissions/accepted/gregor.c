


float Q_rsqrt( float number )
{
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y  = number;
		i  = * ( long * ) &y;                       /* evil floating point bit level hacking*/
		i  = 0x5f3759df - ( i >> 1 );               /* what the fuck? */
		y  = * ( float * ) &i;
		
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );
		y  = y * ( threehalfs - ( x2 * y * y ) );

		return y;
}


int main(){
		float d;
		scanf("%f",&d);
		printf("%f\n", 4.0*1.0/Q_rsqrt(d));
		return 0;
}
